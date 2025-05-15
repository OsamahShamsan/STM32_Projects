#ifndef APP_MENU_H_
#define APP_MENU_H_

#include "menu_manager.h"

// LED Menu
extern const MenuItem led_menu[];
extern const int led_menu_size;

// System Info Menu
extern const MenuItem info_menu[];
extern const int info_menu_size;

// Font Color
extern const MenuItem font_color_menu[];
extern const int font_color_menu_size;

// Background Color
extern const MenuItem bg_color_menu[];
extern const int bg_color_menu_size;

// Font Style
extern const MenuItem font_style_menu[];
extern const int font_style_menu_size;

// Terminal Settings
extern const MenuItem terminal_settings_menu[];
extern const int terminal_settings_menu_size;

// Main Menu
extern const MenuItem main_menu[];
extern const int main_menu_size;

// App menu entry point
void app_menu_run(void);

#endif // APP_MENU_H_
