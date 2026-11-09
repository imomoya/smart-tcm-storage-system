#include "buzzer.h"

void Buzzer_Init(void)
{
    /* TODO: 配置 PC13 为输出（与板载 LED 同脚） */
}

void Buzzer_On(void)
{
    /* TODO: PC13 置位 */
}

void Buzzer_Off(void)
{
    /* TODO: PC13 清零 */
}

void Buzzer_Alarm(bool on)
{
    if (on) {
        Buzzer_On();
    } else {
        Buzzer_Off();
    }
}
