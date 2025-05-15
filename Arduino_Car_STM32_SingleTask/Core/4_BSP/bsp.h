#ifndef BSP_GPIO_H_
#define BSP_GPIO_H_

#include "stm32g4xx_hal.h"

void uart_init(UART_HandleTypeDef *huart);
void uart_send(const char *msg);
char uart_receive_char(void);

void gpio_toggle(GPIO_TypeDef *port, uint16_t pin_mask);
void gpio_set(GPIO_TypeDef *port, uint16_t pin_mask);
void gpio_clear(GPIO_TypeDef *port, uint16_t pin_mask);
uint8_t gpio_read(GPIO_TypeDef *port, uint16_t pin_mask);

#endif // BSP_GPIO_H_
