
#include <stdint.h>
#include <stdbool.h>
#ifndef LED_H
#define LED_H

void led_init(uint16_t LED_PIN);
void led_on(uint16_t LED_PIN);
void led_off(uint16_t LED_PIN);

#endif