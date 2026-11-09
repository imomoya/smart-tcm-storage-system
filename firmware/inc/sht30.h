#ifndef SHT30_H
#define SHT30_H

#include <stdbool.h>

void SHT30_Init(void);
/* TODO: 用 I2C 读 SHT30，成功返回 true，失败返回 false */
bool SHT30_Read(float *temp_c, float *humidity);

#endif
