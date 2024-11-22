#include <stdint.h>

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// Function Prototypes
void motor_init(void);
void motor_forward(uint16_t speed);
void motor_backward(uint16_t speed);
void motor_stop(void);
void motor_set_speed(uint16_t speed);

#endif