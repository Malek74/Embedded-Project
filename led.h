#ifndef rgbLed_h
#define rgbLed_h

#include "pico/stdlib.h"

// define GPIO pins for RGB LED
#define RED_LED_PIN 2
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN 4

/// led init function
void led_init();

// function to turn on the RGB LED with given color
void led_on(bool red, bool green, bool blue);

// function to turn off the RGB LED
void led_all_off();

// function to turn on the all RGB LED
void led_all_on();

#endif