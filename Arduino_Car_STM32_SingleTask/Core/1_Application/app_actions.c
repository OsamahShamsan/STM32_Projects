#include "menu_manager.h"
#include "vt100_terminal.h"
#include "terminal_settings.h"
#include "app_menus.h"
#include <stdio.h>
#include <string.h>

// ==== LED Actions ====
const char* led_toggle_action(void) { gpio_toggle(GPIOA, GPIO_PIN_5); return "[LED] Toggled."; }
const char* led_on_action(void)     { gpio_set(GPIOA, GPIO_PIN_5); return "[LED] ON."; }
const char* led_off_action(void)    { gpio_clear(GPIOA, GPIO_PIN_5); return "[LED] OFF."; }
const char* quit_handler(void)      { return "Exiting BIOS Menu. (System Halted)"; }

// ==== System Info Actions ====
const char* show_board_info(void)       { return "Board: Nucleo G431RB"; }
const char* show_firmware_version(void) { return "Firmware Version: v1.0.0"; }

// ==== Terminal Settings Actions (Indirect handlers using current_key) ====
const char* terminal_set_font_color_handler(void)
{
    uint8_t color = current_key - '1';
    return terminal_settings_set_font_color(color);
}

const char* terminal_set_bg_color_handler(void)
{
    uint8_t color = current_key - '1';
    return terminal_settings_set_background_color(color);
}

const char* terminal_toggle_bold_action(void)      { return terminal_settings_toggle_style(STYLE_BOLD); }
const char* terminal_toggle_italic_action(void)    { return terminal_settings_toggle_style(STYLE_ITALIC); }
const char* terminal_toggle_underline_action(void) { return terminal_settings_toggle_style(STYLE_UNDERLINE); }
