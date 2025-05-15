#ifndef APP_MENU_H_
#define APP_MENU_H_

#include "menu_manager.h"

// ==== Submenus declarations ====
extern const MenuItem led_menu[];
extern const int led_menu_size;

extern const MenuItem info_menu[];
extern const int info_menu_size;

// ==== Main menu declaration ====
extern const MenuItem main_menu[];
extern const int main_menu_size;

// ==== LED action handlers ====
const char* led_toggle_action(void);
const char* led_on_action(void);
const char* led_off_action(void);

// ==== Info action handlers ====
const char* show_board_info(void);
const char* show_firmware_version(void);

// ==== Quit action handler ====
const char* quit_handler(void);

// ==== Application menu system entry point ====
void app_menu_run(void);

#endif // APP_MENU_H_
