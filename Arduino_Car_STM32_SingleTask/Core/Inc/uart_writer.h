/*
#ifndef UART_WRITER_H
#define UART_WRITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"  // for UART_HandleTypeDef

#define UART_TX_BUFFER_SIZE 128
#define UART_MSG_MAX_LEN    256
#define UART_QUEUE_DEPTH    8
#define UART_TX_TIMEOUT_MS  100


// API
bool uart_send_async(UART_HandleTypeDef* huart, const char* str);
void uart_writer_on_tx_complete(UART_HandleTypeDef* huart);
bool uart_is_busy(void);
void uart_writer_test_hi_red(UART_HandleTypeDef* huart);

#ifdef __cplusplus
}
#endif

#endif // UART_WRITER_H
*/
