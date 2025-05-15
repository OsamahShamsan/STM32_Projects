#ifndef TERMINAL_SETTINGS_H_
#define TERMINAL_SETTINGS_H_

#include <stdint.h>

// Style bit masks
#define STYLE_BOLD      (1 << 0)
#define STYLE_ITALIC    (1 << 1)
#define STYLE_UNDERLINE (1 << 2)

// Terminal Settings structure
typedef struct {
    uint8_t font_color;         // 0-7
    uint8_t background_color;   // 0-7
    uint8_t styles;             // Bitmask of STYLE_*
} TerminalSettings;

// Initialization and state management
void terminal_settings_init(void);
void terminal_settings_apply(void);
void terminal_settings_discard(void);
void terminal_settings_reset_all(void);

// Attribute manipulation
const char* terminal_settings_set_font_color(uint8_t color);
const char* terminal_settings_set_background_color(uint8_t color);
const char* terminal_settings_toggle_style(uint8_t style);

// Access cached settings
TerminalSettings* terminal_settings_get_pending(void);

// High-level handlers for Save/Discard (for menu actions)
const char* terminal_settings_save_and_close_action(void);
const char* terminal_settings_reset_all_action(void);
const char* terminal_settings_discard_action(void);

#endif // TERMINAL_SETTINGS_H_
