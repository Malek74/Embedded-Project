#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#ifndef bluetooth_module_H
#define bluetooth_module_H

// variables
#define BLUETOOTH_UART_ID uart0
#define BLUETOOTH_TX_PIN 0
#define BLUETOOTH_RX_PIN 1
#define BLUETOOTH_BAUD_RATE 9600
#define BLUETOOTH_DATA_BITS 8
#define BLUETOOTH_STOP_BITS 1
#define BLUETOOTH_PARITY_BITS UART_PARITY_NONE

// Function prototypes
void bluetooth_init(void);
bool bluetooth_send_data(uint8_t data);
uint8_t bluetooth_read_data(void);

#endif
