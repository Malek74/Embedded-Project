#include "led.h"
#include "pico/stdlib.h"

void led_init(uint16_t LED_PIN)
{
    
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT); // Set LED pin as output
}

void led_on(uint16_t LED_PIN)
{
    gpio_put(LED_PIN, true);
}

void led_off(uint16_t LED_PIN)
{
    gpio_put(LED_PIN, false);
}