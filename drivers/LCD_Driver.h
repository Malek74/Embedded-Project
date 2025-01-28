#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H
#endif

#ifndef STDINT_H
#define STDINT_H
#endif

#include <stdint.h>

#ifndef PICO_STDLIB_H
#define PICO_STDLIB_H
#endif

#include "pico/stdlib.h"

#define LCD_WIDTH 16 // num of col
#define LCD_HEIGHT 2 // num of rows

// definitions for LCD commands -- why ? --> LCD modules require commands to control their functionality and configure how they display text.
// These commands are necessary for proper LCD operation because of the way the LCD's internal controller is designed.
//  dool mn el datasheet bta3et Hitachi HD44780 controller (most popular type)

#define LCD_CMD_CLEAR_DISPLAY 0x01 // clears all text on the screen and resets the cursor to row 0 column 0
#define LCD_CMD_RETURN_HOME 0x02   // moves the cursor to 0,0 position without clearing the display
#define LCD_CMD_ENTRY_MODE 0x04    // configures how the cursor moves after each character is written
#define LCD_CMD_DISPLAY_ON 0x0C    // turns the LCD display on and disables the cursor and blinking
#define LCD_CMD_DISPLAY_OFF 0x08   // turns off the display without clearing its contents

// Pin configuration
#define LCD_PIN_RS 6 // register select --> switching between command and data modes.
#define LCD_PIN_EN 7 // enable pin --> used to trigger the LCD to read the data presented on the data pins
// data pins --> send data to the LCD 4 bits at a time / half byte/ nibble
#define LCD_PIN_D4 8
#define LCD_PIN_D5 9
#define LCD_PIN_D6 10
#define LCD_PIN_D7 11

// function prototypes
void lcd_init(void);
void lcd_clear(void);
void lcd_write_char(char c); // msh lazem nesta3melha
void lcd_write_string(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_send_command(uint8_t cmd);
void lcd_send_data(uint8_t data);
