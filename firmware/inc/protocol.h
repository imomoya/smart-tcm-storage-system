#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

/* 串口协议：纯文本行，方便用串口助手直接看，也方便上位机解析。
 * 上行（下位机 -> 上位机）：
 *   DATA,<格号>,<重量克>,<温度>,<湿度>
 *   例：DATA,1,123.4,25.1,60.2
 * 下行（上位机 -> 下位机）：
 *   SET,TH,<温度上限>,<湿度上限>   例：SET,TH,30,75
 *   TARE,<格号>                    例：TARE,1
 */
void Protocol_SendData(uint8_t slot, float weight_g, float temp_c, float humidity);
bool Protocol_ParseLine(const char *line, float *temp_limit, float *hum_limit,
                        uint8_t *tare_slot);

#endif
