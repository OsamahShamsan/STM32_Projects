#ifndef VT100_TERMINAL_H
#define VT100_TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void vt100_terminal_clear_screen(void);
void vt100_terminal_reset_attributes(void);
void vt100_terminal_set_text_color(uint8_t color);
void vt100_terminal_set_background_color(uint8_t color);
void vt100_terminal_set_bold(void);
void vt100_terminal_set_italic(void);
void vt100_terminal_set_underline(void);
void vt100_terminal_cursor_toggle(void);
void vt100_terminal_write(const char* str);
char vt100_terminal_read_char(void);

/*
void vt100_init(void);
void vt100_printf(const char* fmt, ...);
void vt100_write_SRAM_text(const char* str);
void vt100_write_SRAM_line(const char* str);
void vt100_write_char(char c);
void vt100_write_number(int16_t n, uint8_t width, char fill);
void vt100_goto(uint8_t row, uint8_t col);
void vt100_goto_line(uint8_t line);
void vt100_clear_screen(void);
void vt100_clear_line(void);
void vt100_cursor_hide(void);
void vt100_cursor_show(void);
void vt100_set_color(const char* attr);
void vt100_reset_attributes(void);

void vt100_process_rx_chunk(void);
uint8_t vt100_char_available(void);
uint8_t vt100_read_char(void);

*/

#ifdef __cplusplus
}
#endif

#endif // VT100_TERMINAL_H
