#include "bsp_uart.h"
#include <string.h>

static UART_HandleTypeDef *uart_handle;

void bsp_uart_init(UART_HandleTypeDef *huart)
{
    uart_handle = huart;
}

void bsp_uart_send(const char *msg)
{
    HAL_UART_Transmit(uart_handle, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

char bsp_uart_receive_char(void)
{
    uint8_t c;
    HAL_UART_Receive(uart_handle, &c, 1, HAL_MAX_DELAY);
    return c;
}
