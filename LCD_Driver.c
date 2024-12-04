#include "LCD_Driver.h"
#include "hardware/gpio.h"
#include "pico/time.h"

// Private helper functions
static void lcd_pulse_enable(void);
// static void lcd_send_nibble(uint8_t nibble);

// func to init lcd
void lcd_init(void)
{
    gpio_init(LCD_PIN_RS);
    gpio_set_dir(LCD_PIN_RS, GPIO_OUT);
    gpio_init(LCD_PIN_EN);
    gpio_set_dir(LCD_PIN_EN, GPIO_OUT);
    gpio_init(LCD_PIN_D4);
    gpio_set_dir(LCD_PIN_D4, GPIO_OUT);
    gpio_init(LCD_PIN_D5);
    gpio_set_dir(LCD_PIN_D5, GPIO_OUT);
    gpio_init(LCD_PIN_D6);
    gpio_set_dir(LCD_PIN_D6, GPIO_OUT);
    gpio_init(LCD_PIN_D7);
    gpio_set_dir(LCD_PIN_D7, GPIO_OUT);

    // Delay for LCD power stabilization --> 3amo chat
    sleep_ms(50);

    // Initialization sequence
    lcd_send_nibble(0x03);
    sleep_ms(5);

    lcd_send_nibble(0x03);
    sleep_ms(5);
    lcd_send_nibble(0x03);
    sleep_ms(1);
    lcd_send_nibble(0x02); // Set to 4-bit mode

    // Configure LCD settings
    lcd_send_command(0x28);               // Function set: 4-bit, 2 line, 5x8 dots
    lcd_send_command(LCD_CMD_DISPLAY_ON); // Display ON, cursor OFF
    lcd_clear();
    lcd_send_command(0x06); // Entry mode: Increment cursor, no shift
}

// Function to send a command to the LCD
void lcd_send_command(uint8_t cmd)
{
    gpio_put(LCD_PIN_RS, 0);     // Command mode
    lcd_send_nibble(cmd >> 4);   // Send higher nibble --> shifts the bits of the cmd 4 positions to the right.
    lcd_send_nibble(cmd & 0x0F); // Send lower nibble
}

// Function to send data (e.g., a character) to the LCD
void lcd_send_data(uint8_t data)
{
    gpio_put(LCD_PIN_RS, 1);      // Data mode
    lcd_send_nibble(data >> 4);   // Send higher nibble
    lcd_send_nibble(data & 0x0F); // Send lower nibble
}

// Function to clear the LCD
void lcd_clear(void)
{
    lcd_send_command(LCD_CMD_CLEAR_DISPLAY);
    sleep_ms(2); // Clear command requires extra delay
}

// Function to write a single character --> we may remove this not needed
void lcd_write_char(char c)
{
    lcd_send_data(c);
}

// Function to write a string
void lcd_write_string(const char *str)
{
    while (*str)
    {
        lcd_write_char(*str++);
    }
}

// Function to set the cursor to a specific row and column
void lcd_set_cursor(uint8_t row, uint8_t col)
{
    uint8_t address = 0x00;

    switch (row)
    {
    case 0:
        address = col;
        break; // Row 0 starts at 0x00
    case 1:
        address = 0x40 + col;
        break; // Row 1 starts at 0x40
    default:
        return; // Invalid row
    }

    lcd_send_command(0x80 | address); // Set DDRAM address
}

// Private function to pulse the enable pin
static void lcd_pulse_enable(void)
{
    gpio_put(LCD_PIN_EN, 1);
    sleep_us(1); // Small delay for the pulse
    gpio_put(LCD_PIN_EN, 0);
    sleep_us(50); // Wait for command/data to latch
}

// Private function to send 4 bits (a nibble) to the LCD
static void lcd_send_nibble(uint8_t nibble)
{
    gpio_put(LCD_PIN_D4, (nibble >> 0) & 0x01);
    gpio_put(LCD_PIN_D5, (nibble >> 1) & 0x01);
    gpio_put(LCD_PIN_D6, (nibble >> 2) & 0x01);
    gpio_put(LCD_PIN_D7, (nibble >> 3) & 0x01);
    lcd_pulse_enable();
}
