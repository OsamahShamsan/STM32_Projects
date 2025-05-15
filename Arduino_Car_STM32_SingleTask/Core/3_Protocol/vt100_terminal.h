#ifndef VT100_TERMINAL_H
#define VT100_TERMINAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
	FOREGROUND_COLOR = (uint8_t) 30,
	BACKGROUND_COLOR = (uint8_t) 40
}style;

typedef enum {
	DARK = (uint8_t) 0,
	BRIGHT = (uint8_t) 60
}tone;

typedef enum {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
} Color;

typedef enum {
	SHOW = (uint8_t) 1,
	HIDE = (uint8_t) 0
} visibility;

// Reading Functions
char read_char(void);

// Writing Functions
void write_newline();
void vt100_printf(char* buffer, size_t size, const char *fmt, ...);
void write_SRAM_text(const char* str);
void write_SRAM_text_line(const char* str);
void write_number(/* Takes one parameter => int OR long OR unsigned int OR unsigned long */);

// Style Functions
void set_color(style st , tone to , Color co);
void set_attributes(bool bold, bool underline, bool italic);
void reset_attributes(void);

// Clearing Functions
void clear_screen(void);
void clear_line(void);

// Cursor Functions
void cursor_toggle(void);
void cursor_goto(uint8_t row, uint8_t col);
void cursor_goto_line(uint8_t line);
void set_cursor_visibility(visibility v);



#ifdef __cplusplus
}
#endif

#endif // VT100_TERMINAL_H
