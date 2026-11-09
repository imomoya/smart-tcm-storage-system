/* 下位机主程序：STM32F103C8T6，Keil MDK，C 语言。
 * 初始框架：流程已定，硬件驱动是 TODO，硬件未到货、未联调。
 * 工作流程：上电初始化 -> 周期采集 -> 滤波标定 -> 阈值判断
 *           -> 联动决策 -> 显示上传 -> 下一轮
 *
 * 注意：本文件不含 CubeMX 生成的初始化代码和 Keil 工程文件（.uvprojx），
 * 用 Keil 建工程时再补，不要把本框架当成能直接编译的完整工程。 */

#include "config.h"
#include "hx711.h"
#include "oled.h"
#include "sht30.h"
#include "key.h"
#include "buzzer.h"
#include "protocol.h"

static float temp_limit = TEMP_LIMIT_DEFAULT;
static float hum_limit = HUM_LIMIT_DEFAULT;
static uint8_t selected_slot = 1;

int main(void)
{
    /* 1. 上电初始化 */
    for (uint8_t i = 1; i <= SLOT_COUNT; i++) {
        HX711_Init(i);
    }
    OLED_Init();
    SHT30_Init();
    Key_Init();
    Buzzer_Init();
    /* TODO: 初始化串口 USART1（115200）、时钟、GPIO */

    while (1) {
        /* 2. 周期采集：温湿度是柜内共用的，4 格共用一次读数 */
        float temp_c = 0.0f, humidity = 0.0f;
        bool env_ok = SHT30_Read(&temp_c, &humidity);
        bool alarm = false;

        for (uint8_t slot = 1; slot <= SLOT_COUNT; slot++) {
            /* 3. 滤波标定：HX711_ReadWeightG 内部已做 8 次滑动平均 */
            float weight = HX711_ReadWeightG(slot);
            bool low_stock = (weight < WEIGHT_LOW_LIMIT_G);

            /* 4. 阈值判断 */
            bool env_alarm = env_ok && (temp_c > temp_limit || humidity > hum_limit);
            if (low_stock || env_alarm) {
                alarm = true;
            }

            /* 5. 显示上传：OLED 分时刷新，串口每轮上传一次 */
            OLED_ShowSlot(slot, weight, low_stock);
            if (env_alarm) {
                OLED_ShowAlarm(slot, "温湿度超限");
            }
            Protocol_SendData(slot, weight, temp_c, humidity);
        }

        /* 6. 联动决策：任一格报警就响蜂鸣器 */
        Buzzer_Alarm(alarm);

        /* 7. 按键：选格 / 确认去皮 / 阈值加减 */
        KeyEvent key = Key_Scan();
        if (key == KEY_SELECT) {
            selected_slot = (uint8_t)(selected_slot % SLOT_COUNT + 1);
        } else if (key == KEY_CONFIRM) {
            HX711_Tare(selected_slot);
        } else if (key == KEY_UP) {
            temp_limit += 1.0f;
        } else if (key == KEY_DOWN) {
            temp_limit -= 1.0f;
        }

        /* TODO: 下行命令处理——从串口读一行，调 Protocol_ParseLine，
         * 收到 SET,TH 就改 temp_limit / hum_limit，收到 TARE 就去皮。
         * TODO: 延时 1 秒左右再下一轮，不要空转占满 CPU。 */
    }
}
