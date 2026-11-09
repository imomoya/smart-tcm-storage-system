# 下位机 firmware

STM32F103C8T6，C 语言，Keil MDK。

## 状态

初始框架已写，尚未联调、尚未编译验证。硬件未到货，驱动函数里标了 TODO 的地方都是待填的。

不要把本目录当成能直接编译的完整工程：这里没有 CubeMX 生成的初始化代码，也没有 Keil 工程文件（.uvprojx），用 Keil 建工程时再补。

## 文件

```
inc/config.h      格数、阈值默认值、引脚口径
inc/hx711.h       称重接口
inc/oled.h        OLED 电子标签接口
inc/sht30.h       温湿度接口
inc/key.h         按键接口
inc/buzzer.h      蜂鸣器接口
inc/protocol.h    串口协议：DATA / SET,TH / TARE
src/main.c        主循环：初始化 -> 采集 -> 滤波标定 -> 阈值判断 -> 显示上传
src/hx711.c       滑动平均滤波（8 次）已实现；读原始值待按两线串行时序填
src/oled.c        骨架，待填 SSD1306 驱动
src/sht30.c       骨架，待填 I2C 读取
src/key.c         骨架，待填按键扫描 + 消抖
src/buzzer.c      骨架，待填 PC13 输出
src/protocol.c    文本行协议已实现，串口发送处标了 TODO（改成 USART1 发送）
```

## 设计要求

- 模块化分层：驱动层 / 应用层 / 主控层，前后台状态机
- HX711 采样做滑动平均滤波；去皮、标定、阈值判断
- OLED 分时刷新
- 串口协议上传数据
- 工作流程：上电初始化 → 周期采集 → 滤波标定 → 阈值判断 → 联动决策 → 显示上传 → 下一轮

## 硬件对应关系

- OLED SPI 总线：PA5、PA7（SCK、MOSI），四块共用
- OLED 片选：PA0～PA3（格 1～格 4）
- OLED DC / RES：PB0、PB1，四块共用
- HX711 格 1：PB5、PB8；格 2：PB9、PB10；格 3：PB11、PB12；格 4：PB13、PB14（数据脚 / 时钟脚）
- SHT30：PB6、PB7（SCL / SDA）
- 串口：PA9、PA10（TX / RX）
- 按键：PA4、PA6、PA8、PB15（选格、确认 / 去皮、阈值加、阈值减）
- 蜂鸣器：PC13（与板载 LED 同脚）

注意：HX711 是两线串行时序采集，不是标准 SPI。
