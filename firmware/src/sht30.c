#include "sht30.h"

void SHT30_Init(void)
{
    /* TODO: 配置 PB6(SCL)/PB7(SDA) 为 I2C */
}

bool SHT30_Read(float *temp_c, float *humidity)
{
    /* TODO: 用 I2C 读 SHT30，换算成温度 / 湿度。
     * 硬件未到货，先返回 false，main.c 里按读失败处理，不编假数据。 */
    (void)temp_c;
    (void)humidity;
    return false;
}
