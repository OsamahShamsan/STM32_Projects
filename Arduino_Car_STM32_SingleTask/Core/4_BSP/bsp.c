#include "bsp.h"
#include <string.h>

static UART_HandleTypeDef *uart_handle;

void uart_init(UART_HandleTypeDef *huart)
{
    uart_handle = huart;
}

void uart_send(const char *msg)
{
    HAL_UART_Transmit(uart_handle, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

char uart_receive_char(void)
{
    uint8_t c;
    HAL_UART_Receive(uart_handle, &c, 1, HAL_MAX_DELAY);
    return c;
}

void gpio_toggle(GPIO_TypeDef *port, uint16_t pin_mask)
{
        HAL_GPIO_TogglePin(port, pin_mask);
}

void gpio_set(GPIO_TypeDef *port, uint16_t pin_mask)
{
        HAL_GPIO_WritePin(port, pin_mask, GPIO_PIN_SET);
}

void gpio_clear(GPIO_TypeDef *port, uint16_t pin_mask)
{
        HAL_GPIO_WritePin(port, pin_mask, GPIO_PIN_RESET);
}

uint8_t gpio_read(GPIO_TypeDef *port, uint16_t pin_mask)
{
        return (HAL_GPIO_ReadPin(port, pin_mask) == GPIO_PIN_SET) ? 1 : 0;
}
