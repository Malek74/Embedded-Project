#include "ultrasonic_driver.h"
#include <stdio.h>
#include "pico/stdlib.h"

// Define constants for timeout
#define TIMEOUT_US 30000 // 30 ms timeout (adjust based on your sensor's range)

// Define GPIO pins for trigger and echo
#define TRIG_PIN 28
#define ECHO_PIN 27

// Initialize HC-SR04 pins
void ultrasonic_Init(void)
{
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT); // TRIG_PIN as output
    gpio_put(TRIG_PIN, 0);            // Ensure TRIG_PIN is low initially

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN); // ECHO_PIN as input

    gpio_pull_down(ECHO_PIN);
}

// Sends a 10 µs pulse to the TRIG pin
void ultrasonic_Trigger()
{
    gpio_put(TRIG_PIN, 1);
    sleep_us(10); // Hold high for 10 µs
    gpio_put(TRIG_PIN, 0);
}

// Measures the distance in cm
uint32_t ultrasonic_GetDistance(void)
{
    uint32_t start_time, end_time;

    // Send trigger signal
    ultrasonic_Trigger();

    // Wait for ECHO_PIN to go HIGH (signal start), with timeout
    uint32_t timeout = time_us_32();
    while (gpio_get(ECHO_PIN) == 0)
    {
        if ((time_us_32() - timeout) > TIMEOUT_US)
        {
            return -1; // Timeout - no valid signal
        }
    }

    start_time = time_us_32(); // Record start time

    // Wait for ECHO_PIN to go LOW (signal end), with timeout
    timeout = time_us_32();
    while (gpio_get(ECHO_PIN) == 1)
    {
        if ((time_us_32() - timeout) > TIMEOUT_US)
        {

            return -1; // Timeout - no valid signal
        }
    }

    end_time = time_us_32(); // Record end time

    // Calculate pulse duration in microseconds
    uint32_t pulse_duration = end_time - start_time;

    // Convert duration to distance in cm (speed of sound: ~343 m/s)
    return pulse_duration / 58;
}