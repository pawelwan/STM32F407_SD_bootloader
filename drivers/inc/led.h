#ifndef __LED_H__
#define __LED_H__

#include "stm32f4xx.h"

typedef enum {
    LED_OFF = 0,
    LED_ON = 1,
    LED_TOGGLE = 2
} led_action_t;

typedef enum {
    LED_BLUE = GPIO_Pin_7,
    LED_ORANGE = GPIO_Pin_0,
    LED_RED = GPIO_Pin_1
} led_id_t;

void led_init(void);
void led_deinit(void);
void led_set(led_id_t led_id, led_action_t led_action);
uint8_t led_state(led_id_t led_id);

#endif /* __LED_H */
