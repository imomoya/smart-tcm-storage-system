#include "hx711.h"
#include "config.h"

/* 每格的标定系数和去皮偏移：待砝码标定后填，不要编数字 */
static float scale[SLOT_COUNT] = {1.0f, 1.0f, 1.0f, 1.0f};
static float tare_offset[SLOT_COUNT] = {0.0f, 0.0f, 0.0f, 0.0f};

/* 滑动平均滤波：每格最近 8 次读数取平均，纯逻辑，与硬件无关 */
#define FILTER_LEN 8
static int32_t buf[SLOT_COUNT][FILTER_LEN];
static uint8_t buf_idx[SLOT_COUNT] = {0};

void HX711_Init(uint8_t slot)
{
    (void)slot;
    /* TODO: 配置该格 HX711 的数据脚 / 时钟脚为 GPIO，见 config.h 引脚表 */
}

int32_t HX711_ReadRaw(uint8_t slot)
{
    /* TODO: 按 HX711 两线串行时序读 24 位原始值。
     * 注意：不是标准 SPI，不要按 SPI 驱动写。硬件未到货，先返回 0。 */
    (void)slot;
    return 0;
}

float HX711_ReadWeightG(uint8_t slot)
{
    int32_t raw = HX711_ReadRaw(slot);
    uint8_t i = slot % SLOT_COUNT;

    buf[i][buf_idx[i]] = raw;
    buf_idx[i] = (uint8_t)((buf_idx[i] + 1) % FILTER_LEN);

    int64_t sum = 0;
    for (uint8_t k = 0; k < FILTER_LEN; k++) {
        sum += buf[i][k];
    }
    float avg = (float)sum / FILTER_LEN;
    return avg * scale[i] - tare_offset[i];
}

void HX711_Tare(uint8_t slot)
{
    /* 去皮：把当前滤波后的重量记为偏移，之后读数减掉它 */
    uint8_t i = slot % SLOT_COUNT;
    tare_offset[i] = HX711_ReadWeightG(slot);
}

void HX711_SetScale(uint8_t slot, float s)
{
    scale[slot % SLOT_COUNT] = s;
}
