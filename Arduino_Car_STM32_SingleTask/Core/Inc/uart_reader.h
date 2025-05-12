/*
// -----------------------------
// File: uart_reader.h
// -----------------------------
#ifndef UART_READER_H
#define UART_READER_H

#include <stdint.h>
#include <stdbool.h>

#define UART_RX_BUFFER_SIZE 256

void uart_reader_init(void);
void uart_reader_poll(void); // call periodically if not using IRQ
bool uart_line_available(void);
const char* uart_read_line(void);

#endif // UART_READER_H
*/
