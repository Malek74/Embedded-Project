#include "stdio.h"
#include "pico/stdlib.h"
#include "gyroscope.h"
#include "lcd_driver.h"
#include "hardware/i2c.h"
#include "infrared_sensor.h"
#include "led.h"
#include "motor_driver.h"
#include "ultrasonic_driver.h"
#include "bluetooth_module.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_PIN 2 // Default onboard LED pin for Pico
#define UART_RX_TASK_PRIORITY 1
#define MOTOR_CONTROL_TASK_PRIORITY 2
#define LED_BLINK_TASK_PRIORITY 3
#define INFRA_RED_SENSOR_PIN 14
#define SDA_PIN 4
#define SCL_PIN 5

uint8_t currentSpeedLevel;       // Current speed level of the motor
int16_t accel[3], temp, gyro[3]; // Raw sensor data arrays

float prev_accel_g[3] = {0}; // Previous acceleration values (initialized to 0)

float accel_threshold = 0.2; // Deceleration threshold
char buffer[64];             // Buffer to store ultrasonic & IR sensor data
char buffer2[64];            // Buffer to store gyroscope data
char side[6];
bool isMoving = false;

void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS(); // Disable interrupts to prevent further memory allocation attempts
    for (;;)
    {
    } // Enter an infinite loop to halt the system
}

//  function to handle stack overflows
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    // You can print an error message or handle the stack overflow in other ways
    printf("Stack overflow in task: %s\n", pcTaskName);
    // Optionally, halt the system or take corrective action
    taskDISABLE_INTERRUPTS(); // Disable interrupts to stop any further execution
    for (;;)
    {
        // Infinite loop to halt the system
    }
}

// UART RX Handler Task
void vUartRxTask(void *pvParameters)
{
    while (1)
    {
        while (uart_is_readable(BLUETOOTH_UART_ID))
        {
            uint8_t data = uart_getc(BLUETOOTH_UART_ID); // Read received data
            printf("Received data: %c\n", data);         // Debug: print received data

            if (data == '1') // If data is ASCII '1', turn LED ON
            {
                gpio_put(LED_PIN, 1);
                printf("LED ON\n");
            }
            else if (data == '0') // If data is ASCII '0', turn LED OFF
            {
                gpio_put(LED_PIN, 0);
                printf("LED OFF\n");
            }
            else
            {
                printf("Invalid data received: %c\n", data);
            }

            if (data == 's')
            {
                motor_forward(80);
                if (currentSpeedLevel > 80)
                {
                    led_on(LED_PIN);
                    isMoving = true;
                }
                else
                {
                    led_off(LED_PIN);
                }
                currentSpeedLevel = 80;
            }
            else if (data == 'h')
            {
                motor_forward(128);
                if (currentSpeedLevel > 128)
                {
                    led_on(LED_PIN);
                    isMoving = true;
                }
                else
                {
                    led_off(LED_PIN);
                }
                currentSpeedLevel = 128;
            }
            else if (data == 'g')
            {
                motor_forward(255);
                if (currentSpeedLevel > 255)
                {
                    led_on(LED_PIN);
                    isMoving = true;
                }
                else
                {
                    led_off(LED_PIN);
                }
                currentSpeedLevel = 255;
            }
            else if (data == 'b')
            {
                currentSpeedLevel = -1;
                led_on(LED_PIN);
                isMoving = false;
                motor_stop();
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS); // Delay to yield control to other tasks
    }
}

void vReadAccelTask(void *pvParameters)
{
    // Continuous loop to read and print sensor data
    while (1)
    {
        // Read raw sensor data from MPU6050
        mpu6050_read_raw(accel, gyro, &temp);

        // Convert accelerometer values to g
        float accel_g[3];
        accel_g[0] = accel[0] / ACCEL_SCALE_FACTOR;
        accel_g[1] = accel[1] / ACCEL_SCALE_FACTOR;
        accel_g[2] = accel[2] / ACCEL_SCALE_FACTOR;

        // print gyro values

        if (gpio_get(LED_PIN) == 0)
        {
            // Check for deceleration (negative change in acceleration)
            if ((accel_g[0] - prev_accel_g[0] < -accel_threshold) || (accel_g[1] - prev_accel_g[1] < -accel_threshold))
            {
                // Deceleration detected, turn on the LED
                led_on(LED_PIN);
            }
            else
            {
                // No deceleration, turn off the LED
                led_off(LED_PIN);
            }
        }
        // Store the current acceleration values for the next iteration
        prev_accel_g[0] = accel_g[0];
        prev_accel_g[1] = accel_g[1];
        prev_accel_g[2] = accel_g[2];

        // Convert gyroscope values to degrees per second (dps)
        float gyro_dps[3];
        gyro_dps[0] = gyro[0] / GYRO_SCALE_FACTOR;
        gyro_dps[1] = gyro[1] / GYRO_SCALE_FACTOR;
        gyro_dps[2] = gyro[2] / GYRO_SCALE_FACTOR;

        // Convert temperature to degrees Celsius
        float temp_celsius = temp / 340.00 + 36.53;

        sprintf(buffer2, "X: %.2f Y: %.2f Z: %.2f", gyro_dps[0], gyro_dps[1], gyro_dps[2]);
        // Print sensor values
        printf("Accel: X=%.2f g, Y=%.2f g, Z=%.2f g\n", accel_g[0], accel_g[1], accel_g[2]);
        printf("Gyro: X=%.2f dps, Y=%.2f dps, Z=%.2f dps\n", gyro_dps[0], gyro_dps[1], gyro_dps[2]);
        printf("Temperature: %.2f C\n", temp_celsius);

        // Delay for a period (e.g., 100ms) to allow other tasks to run
        vTaskDelay(pdMS_TO_TICKS(100)); // Adjust delay as needed
    }
}

void vObjectDetectionTask(void *pvParameters)
{
    while (1)
    {
        sleep_ms(1000); // Clear LCD screen

        lcd_clear();

        int distance = ultrasonic_GetDistance();
        if (distance == -1)
        {
            sprintf(buffer, "Far|Side: %s", side);
            lcd_write_string(buffer); // Display "Far" if the distance is invalid
            lcd_set_cursor(1, 0);
            lcd_write_string(buffer2);
        }
        else
        {
            // Display the measured distance in cm if it's valid
            sprintf(buffer, "%d cm|Side: %s", distance, side);
            lcd_write_string(buffer); // Display "Far" if the distance is invalid
            lcd_set_cursor(1, 0);
            lcd_write_string(buffer2); //
        }

        if (distance < 10 && distance > 0 && isMoving)
        {
            motor_forward(50);
            currentSpeedLevel = 50;
        }
        else if (distance < 20 && distance > 0 && isMoving)
        {
            motor_forward(100);
            currentSpeedLevel = 100;
        }
        else if (distance < 30 && distance > 0 && isMoving)
        {
            motor_forward(150);
            currentSpeedLevel = 150;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void vSideDetectionTask(void *pvParameters)
{
    while (1)
    {
        sleep_ms(1000);
        if (!(infrared_sensor_is_triggered(INFRA_RED_SENSOR_PIN)))
        {
            sprintf(side, "Busy");
        }
        else
        {
            sprintf(side, "Free");
        }
    }
}

void vPrintTask(void *pvParameters)
{
    while (1)
    {
        lcd_clear();
        lcd_write_string(buffer);
        lcd_set_cursor(1, 0);
        lcd_write_string(buffer2);
        vTaskDelay(pdMS_TO_TICKS(200));
        sleep_ms(1000);
    }
}

// LED Blink Task (if required)
int main(void)
{
    // Initialize all peripherals
    stdio_init_all();
    lcd_init();
    // infrared_sensor_init();
    led_init(LED_PIN);
    motor_init();
    ultrasonic_Init();
    bluetooth_init();
    infrared_sensor_init(INFRA_RED_SENSOR_PIN);
    lcd_clear(); // Clear LCD screen

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

    isMoving = false;  

    // Create FreeRTOS tasks
    xTaskCreate(vUartRxTask, "UART RX Task", 256, NULL, UART_RX_TASK_PRIORITY, NULL);
    xTaskCreate(vReadAccelTask, "Accel Task", 256, NULL, 1, NULL);
    xTaskCreate(vObjectDetectionTask, "Object Detection Task", 256, NULL, 1, NULL);
    xTaskCreate(vSideDetectionTask, "Side Detection Task", 256, NULL, 1, NULL);
    xTaskCreate(vPrintTask, "Print Task", 256, NULL, 1, NULL);

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // If the scheduler starts successfully, the code below will not run
    for (;;)
    {
    }

    return 0; // Technically unreachable
}
