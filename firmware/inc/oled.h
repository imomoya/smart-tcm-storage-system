#ifndef OLED_H
#define OLED_H

#include <stdint.h>
#include <stdbool.h>

/* 每格 1 块 0.96 寸 OLED，SPI 7 针版 SSD1306，4 块共用 SPI 总线、独立片选 */
void OLED_Init(void);
void OLED_ShowSlot(uint8_t slot, float weight_g, bool low_stock);
void OLED_ShowAlarm(uint8_t slot, const char *msg);

#endif
