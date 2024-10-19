#include "led.h"

void led_init()
{

    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
}

void led_on(bool red, bool green, bool blue)
{
    gpio_put(BLUE_LED_PIN, blue);
    gpio_put(GREEN_LED_PIN, green);
    gpio_put(RED_LED_PIN, red);
}

void led_all_off()
{
    gpio_put(BLUE_LED_PIN, false);
    gpio_put(GREEN_LED_PIN, false);
    gpio_put(RED_LED_PIN, false);
}

void led_all_on()
{
    gpio_put(BLUE_LED_PIN, true);
    gpio_put(GREEN_LED_PIN, true);
    gpio_put(RED_LED_PIN, true);
}
