#ifndef UART_DMA_H
#define UART_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32g4xx_hal.h"

#define UART_RX_BUFFER_SIZE  256

// --- Initialization: must pass the UART handle explicitly ---
void uart_dma_init(UART_HandleTypeDef* huart);

// --- Must be called from USART IRQ or DMA IRQ when idle or HT/FT ---
void uart_dma_handle_idle(UART_HandleTypeDef* huart);

// --- Get newly received bytes (since last check) ---
const uint8_t* uart_dma_get_new_bytes(uint16_t* count);

// --- Send data using UART DMA (vt100 uses this only) ---
void uart_dma_send(const uint8_t* data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif // UART_DMA_H
