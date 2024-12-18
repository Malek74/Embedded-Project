#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/gpio.h"

// Define the GPIO pin connected to the IR sensor

// Function to initialize the infrared sensor
void infrared_sensor_init(uint sensor_pin);

// Function to check if the infrared sensor is triggered (digital read)
bool infrared_sensor_is_triggered(uint sensor_pin);

// Function to read distance from the IR sensor (analog read)
uint16_t IR_Sensor_Read(void);

// Function to detect deceleration based on IR sensor readings
int IR_Sensor_Detect_Deceleration(uint16_t previous_distance, uint16_t current_distance);

#endif // INFRARED_SENSOR_H