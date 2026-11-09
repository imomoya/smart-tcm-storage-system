#ifndef HX711_H
#define HX711_H

#include <stdint.h>
#include <stdbool.h>

void HX711_Init(uint8_t slot);
int32_t HX711_ReadRaw(uint8_t slot);          /* TODO: 按两线串行时序读原始值 */
float HX711_ReadWeightG(uint8_t slot);        /* 滑动平均滤波后的重量（克） */
void HX711_Tare(uint8_t slot);                /* 去皮：把当前重量记为 0 */
void HX711_SetScale(uint8_t slot, float scale); /* 标定系数：克 / 原始值，待砝码标定后填 */

#endif
