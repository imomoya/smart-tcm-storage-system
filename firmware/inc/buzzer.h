#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Alarm(bool on); /* 报警开 / 关，有源蜂鸣器，PC13 */

#endif
