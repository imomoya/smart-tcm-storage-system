#include "oled.h"

/* TODO: 填 SSD1306 的 SPI 驱动。
 * 4 块 OLED 共用 PA5(SCK)/PA7(MOSI)，片选 PA0~PA3 各管一格，
 * DC/RES 用 PB0/PB1，共用。先只实现一格，跑通再扩到 4 格。 */

void OLED_Init(void)
{
    /* TODO: 初始化 SPI + 各片选脚，逐块发 SSD1306 初始化命令 */
}

void OLED_ShowSlot(uint8_t slot, float weight_g, bool low_stock)
{
    /* TODO: 在第 slot 格的 OLED 上显示格号和重量，缺药时显示提示 */
    (void)slot;
    (void)weight_g;
    (void)low_stock;
}

void OLED_ShowAlarm(uint8_t slot, const char *msg)
{
    /* TODO: 在第 slot 格的 OLED 上显示报警文字 */
    (void)slot;
    (void)msg;
}
