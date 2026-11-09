#include "protocol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* TODO: 把 printf 改成串口发送（USART1，PA9/PA10）。
 * 现在先用 printf 占位，方便在 PC 上看协议格式。 */

void Protocol_SendData(uint8_t slot, float weight_g, float temp_c, float humidity)
{
    printf("DATA,%d,%.1f,%.1f,%.1f\r\n", slot, weight_g, temp_c, humidity);
}

bool Protocol_ParseLine(const char *line, float *temp_limit, float *hum_limit,
                        uint8_t *tare_slot)
{
    /* SET,TH,30,75 */
    if (strncmp(line, "SET,TH,", 7) == 0) {
        float t = 0, h = 0;
        if (sscanf(line + 7, "%f,%f", &t, &h) == 2) {
            *temp_limit = t;
            *hum_limit = h;
            return true;
        }
        return false;
    }
    /* TARE,1 */
    if (strncmp(line, "TARE,", 5) == 0) {
        int slot = atoi(line + 5);
        if (slot >= 1 && slot <= 4) {
            *tare_slot = (uint8_t)slot;
            return true;
        }
    }
    return false;
}
