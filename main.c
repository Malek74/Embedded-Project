#include <stdio.h>
#include "pico/stdlib.h"
#include "led.h"

int main()
{

    const uint led_pin = 6;

    // Initialize LED pin
    led_init();

    while (true)
    {

        // delay of 5 seconds
        sleep_ms(5000);

        led_on(true, false, false);
        sleep_ms(1000); // Red LED on for 1 second
        led_all_off();

        led_on(false, true, false);
        sleep_ms(1000); // Green LED on for 1 second
        led_all_off();

        led_on(false, false, true);
        sleep_ms(1000); // Blue LED on for 1 second
        led_all_off();

        // Turn on all LEDs for 2 seconds
        led_all_on();
        sleep_ms(2000); // All LEDs on for 2 seconds
        led_all_off();

        // The total cycle takes 10 seconds (5 seconds initial off, 3 seconds individual LEDs, 2 seconds all LEDs)
    }

    // // Loop forever
    // // while (true) {

    //     // Blink LED
    //     printf("Blinking!\r\n");
    //     gpio_put(led_pin, true);
    //     sleep_ms(1000);
    //     gpio_put(led_pin, false);
    //     sleep_ms(1000);
    // }
}