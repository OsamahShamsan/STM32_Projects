#include "vt100_terminal.h"
#include "vt100_esc.h"
#include <bsp.h>

char read_char(void) { return uart_receive_char(); }

void write_newline(){
	uart_send(NEW_LINE);
}

void vt100_printf(char* buffer, size_t size, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, size, fmt, args);
    va_end(args);
    uart_send(buffer);
}

void write_SRAM_text(const char* str) { uart_send(str); }

void write_SRAM_text_line(const char* str) {
	uart_send(str);
	uart_send(NEW_LINE);
}

// Internal helpers DONT USE THESE. Instead use write_number(); see .h file
void write_SRAM_int(int num) {
    char buf[16];
    sprintf(buf, "%d", num);
    uart_send(buf);
}
void write_SRAM_uint(unsigned int num) {
    char buf[16];
    sprintf(buf, "%u", num);
    uart_send(buf);
}
void write_SRAM_long(long num) {
    char buf[32];
    sprintf(buf, "%ld", num);
    uart_send(buf);
}
void write_SRAM_ulong(unsigned long num) {
    char buf[32];
    sprintf(buf, "%lu", num);
    uart_send(buf);
}

/*
static void write_SRAM_float(float num) {
    char buf[32];
    int32_t int_part = (int32_t)num;
    int32_t frac_part = (int32_t)((num - int_part) * 10000);

    // Handle negative fractions (ensure always positive)
    if (frac_part < 0) frac_part = -frac_part;

    sprintf(buf, "%ld.%04ld", (long)int_part, (long)frac_part);
    uart_send(buf);
}

static void write_SRAM_double(double num) {
    char buf[32];
    int64_t int_part = (int64_t)num;
    int64_t frac_part = (int64_t)((num - int_part) * 10000);

    if (frac_part < 0) frac_part = -frac_part;

    sprintf(buf, "%lld.%04lld", (long long)int_part, (long long)frac_part);
    uart_send(buf);
}
*/




void set_color(style st , tone to , Color co)
{
    char cmd[16];
    uint8_t c  = st + to + co;
    sprintf(&cmd[0], "\x1B[%dm", c);
    uart_send(cmd);
}

void set_attributes(bool bold, bool underline, bool italic)
{
	char cmd[8] = "\x1B[";
	uint8_t len = 2;

	if (bold)       len += sprintf(&cmd[len], "1;");
	if (underline)  len += sprintf(&cmd[len], "4;");
	if (italic)     len += sprintf(&cmd[len], "3;");

	if (len == 2) { // No attributes added
	        len += sprintf(&cmd[len], "0m");
	} else {
	        cmd[len - 1] = 'm';
	}

    uart_send(cmd);
}

void reset_attributes(void) { uart_send(VT100_RESET_ATTRIBUTES); }

const char *color(Color c) {
    switch (c) {
        case BLACK:   		return "\x1B[30m";
        case RED:     		return "\x1B[31m";
        case GREEN:   		return "\x1B[32m";
        case YELLOW:  		return "\x1B[33m";
        case BLUE:    		return "\x1B[34m";
        case MAGENTA: 		return "\x1B[35m";
        case CYAN:    		return "\x1B[36m";
        case WHITE:   		return "\x1B[37m";
        default:            return "\x1B[0m";
    }
}
const char *color(Color c);



void clear_screen(void)
{
    uart_send(VT100_CLEAR_SCREEN);
    uart_send(VT100_CURSOR_HOME);
}

void clear_line(void) { uart_send(VT100_CLEAR_LINE); }


void cursor_toggle(void)
{
    static uint8_t visible = 1;
    uart_send(visible ? VT100_CURSOR_HIDE : VT100_CURSOR_SHOW);
    visible = !visible;
}


void cursor_goto(uint8_t row, uint8_t col) {
    char cmd[16];
    snprintf(cmd, sizeof(cmd), VT100_CURSOR_POSITION, row, col);
    uart_send(cmd);
}

void cursor_goto_line(uint8_t line) {
	cursor_goto(line, 1);
}

void set_cursor_visibility(visibility v) {
	(v = true) ? uart_send(VT100_CURSOR_SHOW) : uart_send(VT100_CURSOR_HIDE);
}


#ifdef __STDC_VERSION__
    #if __STDC_VERSION__ >= 201112L  // C11 or newer

        // Universal interface using _Generic (C11 feature)
		#undef write_number  // ensure clean redefinition

        #define send_number(n) _Generic((n), \
            int: 			write_SRAM_int, \
            unsigned int: 	write_SRAM_uint, \
            long: 			write_SRAM_long, \
            unsigned long:  write_SRAM_ulong, \
            default: 		write_SRAM_int \
        )(n)

    #else  // C99 or older fallback

        // Fallback: must explicitly call the correct function
		#undef write_number
        #define send_number(n) write_SRAM_int((n))  // fallback only supports int-like

    #endif
#else
    // Compiler does not support __STDC_VERSION__, assume very old C (pre C99)
	#undef write_number
    #define send_number(n) write_SRAM_int((n))
#endif

/*


void vt100_write_number(int16_t n, uint8_t width, char fill) {
	char buffer[VT100_NUMBER_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%*c%d", width - snprintf(NULL, 0, "%d", n), fill, n);

    // Simpler and safer pattern using format string creation:
    char format[VT100_FORMAT_BUFFER_SIZE];
    snprintf(format, sizeof(format), "%%%c%dd", fill, width);
    snprintf(buffer, sizeof(buffer), format, n);

    vt100_send(buffer);
}







*/
