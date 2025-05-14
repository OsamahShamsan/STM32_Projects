#ifndef BSP_UART_H_
#define BSP_UART_H_

#include "stm32g4xx_hal.h"

void bsp_uart_init(UART_HandleTypeDef *huart);
void bsp_uart_send(const char *msg);
char bsp_uart_receive_char(void);

#endif
