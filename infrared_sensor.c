#include "infrared_sensor.h"
#include "hardware/adc.h"
#include <stdio.h>

// Initialize the infrared sensor (for digital trigger and analog read)
void infrared_sensor_init(uint sensor_pin)
{
    gpio_init(sensor_pin);             // Initialize the GPIO pin for the sensor
    gpio_set_dir(sensor_pin, GPIO_IN); // Set the pin direction as input

    // Initialize the ADC for analog distance measurement
    adc_init();
    adc_gpio_init(26);   // Assuming ADC channel is connected to GPIO 26, modify if needed
    adc_select_input(0); // Choose the correct ADC channel, e.g., 0 for channel 0
}

// Check if the infrared sensor is triggered (digital read)
bool infrared_sensor_is_triggered(uint sensor_pin)
{
    return gpio_get(sensor_pin); // Return the state of the sensor (1 if triggered, 0 otherwise)
}

// Function to read distance from the IR sensor via ADC (analog read)
uint16_t IR_Sensor_Read(void)
{
    return adc_read(); // Read from the ADC
}

// Function to detect deceleration
int IR_Sensor_Detect_Deceleration(uint16_t previous_distance, uint16_t current_distance)
{
    const uint16_t deceleration_threshold = 50; // Adjust based on testing

    int16_t distance_change = previous_distance - current_distance;

    // Return 1 if deceleration is detected, otherwise 0
    return distance_change > deceleration_threshold ? 1 : 0;
}