#include "bluetooth_module.h"

void bluetooth_init(void)
{
    uart_init(BLUETOOTH_UART_ID, BLUETOOTH_BAUD_RATE);
    gpio_set_function(BLUETOOTH_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(BLUETOOTH_RX_PIN, GPIO_FUNC_UART);

    uart_set_baudrate(BLUETOOTH_UART_ID, BLUETOOTH_BAUD_RATE);
    uart_set_hw_flow(BLUETOOTH_UART_ID, false, false);
    uart_set_format(BLUETOOTH_UART_ID, BLUETOOTH_DATA_BITS, BLUETOOTH_STOP_BITS, BLUETOOTH_PARITY_BITS);
    uart_set_fifo_enabled(BLUETOOTH_UART_ID, false);
}

bool bluetooth_send_data(uint8_t data)
{
    if (uart_is_writable(BLUETOOTH_UART_ID))
    {
        uart_write_blocking(BLUETOOTH_UART_ID, &data, 1);
        return true;
    }

    return false;
}

uint8_t bluetooth_read_data(void)
{
    if (uart_is_readable(BLUETOOTH_UART_ID))
    {
        return uart_getc(BLUETOOTH_UART_ID);
    }

    return -1;
}