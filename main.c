#include "stdio.h"
#include "pico/stdlib.h"
#include "gyroscope.h"
#include "lcd_driver.h"
#include "hardware/i2c.h"
#include "infrared_sensor.h"
#include "led.h"
#include "motor_driver.h"
#include "ultrasonic_driver.h"

#define INFRA_RED_SENSOR_PIN 15
#define LED_PIN 16
#define SDA_PIN 4
#define SCL_PIN 5

int main()
{
    stdio_init_all();
    lcd_init();
    infrared_sensor_init(INFRA_RED_SENSOR_PIN);
    led_init(LED_PIN);
    motor_init();
    ultrasonic_Init();

    lcd_clear();

    // Initialize I2C for MPU6050
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Reset and configure MPU6050
    mpu6050_reset();
    mpu6050_configure();

    // Check MPU6050 communication
    uint8_t who_am_i = 0;
    uint8_t reg = WHO_AM_I_REG;
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, &who_am_i, 1, false);
    printf("MPU6050 WHO_AM_I register: 0x%02X\n", who_am_i);

    if (who_am_i != 0x68)
    {
        printf("Error: MPU6050 not detected!\n");
        while (1)
            ; // Stop execution if MPU6050 is not found
    }

    // Variables to hold raw sensor data
    int16_t accel[3], gyro[3], temp;

    // Continuous loop to read and print sensor darta
    while (1)
    {
        // Read raw sensor data
        mpu6050_read_raw(accel, gyro, &temp);

        // Convert accelerometer values to g
        float accel_g[3];
        accel_g[0] = accel[0] / ACCEL_SCALE_FACTOR;
        accel_g[1] = accel[1] / ACCEL_SCALE_FACTOR;
        accel_g[2] = accel[2] / ACCEL_SCALE_FACTOR;

        // Convert gyroscope values to degrees per second (dps)
        float gyro_dps[3];
        gyro_dps[0] = gyro[0] / GYRO_SCALE_FACTOR;
        gyro_dps[1] = gyro[1] / GYRO_SCALE_FACTOR;
        gyro_dps[2] = gyro[2] / GYRO_SCALE_FACTOR;

        // Convert temperature to degrees Celsius
        float temp_celsius = temp / 340.00 + 36.53;

        // Print sensor values
        printf("Accel: X=%.2f g, Y=%.2f g, Z=%.2f g \n  ", accel_g[0], accel_g[1], accel_g[2]);

        sleep_ms(500); // Delay for readability

        //////////////////////////Code to test the LCD+Infrared+LED+UltraSonic//////////////////////////
        lcd_clear();

        if (!(infrared_sensor_is_triggered(INFRA_RED_SENSOR_PIN)))
        {
            lcd_set_cursor(0, 0);
            lcd_write_string("Object Detected");
            led_on(LED_PIN);

            motor_stop();

            lcd_set_cursor(1, 0);
            lcd_write_string("Distance: ");
            int distance = ultrasonic_GetDistance();
            if (distance == -1)
            {
                lcd_write_string("Far");
            }
            {
                char buffer[64];
                sprintf(buffer, "%d cm", distance);
                lcd_write_string(buffer);
            }
        }
        else
        {
            lcd_set_cursor(0, 0);
            lcd_write_string("No Object Aside");
            led_off(LED_PIN);

            lcd_set_cursor(1, 0);
            lcd_write_string("Distance: ");

            int distance = ultrasonic_GetDistance();
            if (distance == -1)
            {
                lcd_write_string("Far");
            }
            else
            {

                char buffer[64];
                sprintf(buffer, "%d cm", distance);
                lcd_write_string(buffer);
            }
        }

        sleep_ms(1000);
    }

    // test motor speed using PWM
    // for (int i = 50; i < 255; i++)
    // {
    //     motor_forward(i);
    //     sleep_ms(100);
    // }

    {
        return 0;
    }
}