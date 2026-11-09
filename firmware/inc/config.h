#ifndef CONFIG_H
#define CONFIG_H

/* 初始框架：只定口径，不含已实测的数据。
 * 称重精度、传感器量程以实测为准，不要把这里的默认值当成结论。 */

#define SLOT_COUNT 4

/* 温湿度报警默认值，可由上位机下发修改 */
#define TEMP_LIMIT_DEFAULT 30.0f
#define HUM_LIMIT_DEFAULT 75.0f

/* 称重：每格 1 只传感器 + 1 片 HX711
 * HX711 是两线串行时序，不是标准 SPI。量程 1kg / 5kg 待对比后定。 */
#define WEIGHT_LOW_LIMIT_G 50.0f /* 缺药报警阈值（克），初值，待实测后调 */

/* 串口：PA9(TX) / PA10(RX)，CH340 连 PC */
#define UART_BAUD 115200

/* 引脚（见 hardware/README.md 的引脚表）：
 * OLED SPI: PA5(SCK) PA7(MOSI)，片选 PA0~PA3，DC/RES PB0/PB1
 * HX711: 格1 PB5/PB8，格2 PB9/PB10，格3 PB11/PB12，格4 PB13/PB14
 * SHT30: PB6(SCL) PB7(SDA)
 * 按键: PA4 PA6 PA8 PB15
 * 蜂鸣器: PC13 */

#endif
