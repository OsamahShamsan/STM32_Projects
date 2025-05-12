#include "vt100.h"
#include "vt100_esc.h"
#include "uart_dma.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define VT100_PRINT_BUFFER_SIZE  64
#define VT100_CMD_BUFFER_SIZE 	 32
#define VT100_NUMBER_BUFFER_SIZE 16
#define VT100_FORMAT_BUFFER_SIZE 8

static void vt100_send(const char* str) {
    uart_dma_send((const uint8_t*)str, strlen(str));
}

static void vt100_send_char(char c) {
    uart_dma_send((const uint8_t*)&c, 1);
}

void vt100_write_SRAM_text(const char* str) {
    vt100_send(str);
}

void vt100_write_SRAM_line(const char* str) {
    vt100_send(str);
    vt100_send("\r\n");
}

void vt100_write_char(char c) {
    vt100_send_char(c);
}

void vt100_printf(const char* fmt, ...) {
	char buffer[VT100_PRINT_BUFFER_SIZE];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    vt100_send(buffer);
}

void vt100_write_number(int16_t n, uint8_t width, char fill) {
	char buffer[VT100_NUMBER_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%*c%d", width - snprintf(NULL, 0, "%d", n), fill, n);

    // Simpler and safer pattern using format string creation:
    char format[VT100_FORMAT_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%%%c%dd", fill, width);
    snprintf(buffer, sizeof(buffer), format, n);

    vt100_send(buffer);
}

// VT100 controls
void vt100_goto(uint8_t row, uint8_t col) {
    char cmd[VT100_CMD_BUFFER_SIZE];
    snprintf(cmd, sizeof(cmd), VT100_CURSOR_POSITION, row, col);
    vt100_send(cmd);
}

void vt100_goto_line(uint8_t line) {
    vt100_goto(line, 1);
}

void vt100_clear_screen(void) {
    vt100_send(VT100_CLEAR_SCREEN);
    vt100_send(VT100_CURSOR_HOME);
}

void vt100_clear_line(void) {
    vt100_send(VT100_CLEAR_LINE);
}

void vt100_cursor_hide(void) {
    vt100_send(VT100_CURSOR_HIDE);
}

void vt100_cursor_show(void) {
    vt100_send(VT100_CURSOR_SHOW);
}

void vt100_set_color(const char* attr) {
    if (attr) vt100_send(attr);
}

void vt100_reset_attributes(void) {
    vt100_send(VT100_RESET_ATTRIBUTES);
}

// RX buffering
static uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static uint16_t rx_head = 0;
static uint16_t rx_tail = 0;

void vt100_process_rx_chunk(void) {
    uint16_t new_bytes;
    const uint8_t* data = uart_dma_get_new_bytes(&new_bytes);

    for (uint16_t i = 0; i < new_bytes; i++) {
        rx_buffer[rx_head++] = data[i];
        if (rx_head >= UART_RX_BUFFER_SIZE) rx_head = 0;
    }
}

uint8_t vt100_char_available(void) {
    return rx_head != rx_tail;
}

uint8_t vt100_read_char(void) {
    if (rx_head == rx_tail) return 0;
    uint8_t c = rx_buffer[rx_tail++];
    if (rx_tail >= UART_RX_BUFFER_SIZE) rx_tail = 0;
    return c;
}
