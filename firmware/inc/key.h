#ifndef KEY_H
#define KEY_H

#include <stdint.h>

typedef enum {
    KEY_NONE = 0,
    KEY_SELECT,  /* 选格 */
    KEY_CONFIRM, /* 确认 / 去皮 */
    KEY_UP,      /* 阈值加 */
    KEY_DOWN     /* 阈值减 */
} KeyEvent;

void Key_Init(void);
KeyEvent Key_Scan(void); /* TODO: 扫描 4 个按键，带消抖，返回本次按下的键 */

#endif
