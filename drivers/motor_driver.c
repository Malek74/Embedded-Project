
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "motor_driver.h"

// Define GPIO pins for the motor
#define IN1 21   // Connect to H-Bridge IN1
#define IN2 20   // Connect to H-Bridge IN2
#define ENABLE 19.














 // Connect to H-Bridge ENABLE (PWM for speed control)

// PWM slice and channel variables
uint pwm_slice_num;

// Initialize motor GPIO pins
void motor_init(void)
{
    // Initialize motor control pins
    gpio_init(IN1);
    gpio_init(IN2);
    gpio_set_dir(IN1, GPIO_OUT);
    gpio_set_dir(IN2, GPIO_OUT);

    // Initialize PWM pin
    gpio_set_function(ENABLE, GPIO_FUNC_PWM);
    pwm_slice_num = pwm_gpio_to_slice_num(ENABLE);

    // Configure PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 10.0f);
    pwm_init(pwm_slice_num, &config, true);

    // Set initial PWM level (motor off)
    pwm_set_gpio_level(ENABLE, 0);

    // Ensure motor is initially stopped
    gpio_put(IN1, 0);
    gpio_put(IN2, 0);
}

// Set motor speed (0 to 255 for duty cycle)
void motor_set_speed(uint16_t speed)
{
    uint16_t duty_cycle = (speed * 65535) / 255; // Scale 0-255 to 0-65535
    pwm_set_gpio_level(ENABLE, duty_cycle);
}

// Move motor forward
void motor_forward(uint16_t speed)
{
    gpio_put(IN1, 1);
    gpio_put(IN2, 0);
    motor_set_speed(speed); // Set speed using PWM
}

// Move motor backward
void motor_backward(uint16_t speed)
{
    gpio_put(IN1, 0);
    gpio_put(IN2, 1);
    motor_set_speed(speed); // Set speed using PWM
}

// Stop the motor
void motor_stop(void)
{
    motor_set_speed(0); // Disable PWM
    gpio_put(IN1, 0);
    gpio_put(IN2, 0);
}