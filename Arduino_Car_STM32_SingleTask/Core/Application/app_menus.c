#include "app_menus.h"
#include "terminal_settings.h"
#include "menu_manager.h"
#include "bsp_gpio.h"
#include "app_actions.h"

// ==== LED Menu ====
const MenuItem led_menu[] = {
    {'1', "Toggle LED", led_toggle_action, NULL, 0},
    {'2', "LED ON", led_on_action, NULL, 0},
    {'3', "LED OFF", led_off_action, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int led_menu_size = sizeof(led_menu) / sizeof(MenuItem);

// ==== System Info Menu ====
const MenuItem info_menu[] = {
    {'1', "Board Info", show_board_info, NULL, 0},
    {'2', "Firmware Version", show_firmware_version, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int info_menu_size = sizeof(info_menu) / sizeof(MenuItem);

// ==== Font Color Submenu ====
const MenuItem font_color_menu[] = {
    {'1', "Black", terminal_set_font_color_handler, NULL, 0},
    {'2', "Red", terminal_set_font_color_handler, NULL, 0},
    {'3', "Green", terminal_set_font_color_handler, NULL, 0},
    {'4', "Yellow", terminal_set_font_color_handler, NULL, 0},
    {'5', "Blue", terminal_set_font_color_handler, NULL, 0},
    {'6', "Magenta", terminal_set_font_color_handler, NULL, 0},
    {'7', "Cyan", terminal_set_font_color_handler, NULL, 0},
    {'8', "White", terminal_set_font_color_handler, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int font_color_menu_size = sizeof(font_color_menu) / sizeof(MenuItem);

// ==== Background Color Submenu ====
const MenuItem bg_color_menu[] = {
    {'1', "Black", terminal_set_bg_color_handler, NULL, 0},
    {'2', "Red", terminal_set_bg_color_handler, NULL, 0},
    {'3', "Green", terminal_set_bg_color_handler, NULL, 0},
    {'4', "Yellow", terminal_set_bg_color_handler, NULL, 0},
    {'5', "Blue", terminal_set_bg_color_handler, NULL, 0},
    {'6', "Magenta", terminal_set_bg_color_handler, NULL, 0},
    {'7', "Cyan", terminal_set_bg_color_handler, NULL, 0},
    {'8', "White", terminal_set_bg_color_handler, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int bg_color_menu_size = sizeof(bg_color_menu) / sizeof(MenuItem);

// ==== Font Style Submenu ====
const MenuItem font_style_menu[] = {
    {'1', "Bold",      terminal_toggle_bold_action, NULL, 0},
    {'2', "Italic",    terminal_toggle_italic_action, NULL, 0},
    {'3', "Underline", terminal_toggle_underline_action, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int font_style_menu_size = sizeof(font_style_menu) / sizeof(MenuItem);

// ==== Terminal Settings Cascading Menu ====
const MenuItem terminal_settings_menu[] = {
    {'1', "Font Color", NULL, font_color_menu, font_color_menu_size},
    {'2', "Background Color", NULL, bg_color_menu, bg_color_menu_size},
    {'3', "Font Style", NULL, font_style_menu, font_style_menu_size},
    {'4', "Reset Attributes", terminal_settings_reset_all_action, NULL, 0},
    {'5', "Save and Close", terminal_settings_save_and_close_action, NULL, 0},
    {'6', "Discard and Close", terminal_settings_discard_action, NULL, 0}
};
const int terminal_settings_menu_size = sizeof(terminal_settings_menu) / sizeof(MenuItem);

// ==== Main Menu (reordered as requested) ====
const MenuItem main_menu[] = {
    {'1', "System Info", NULL, info_menu, info_menu_size},
    {'2', "Terminal Settings", NULL, terminal_settings_menu, terminal_settings_menu_size},
    {'3', "LED Control", NULL, led_menu, led_menu_size},
    {'q', "Quit", quit_handler, NULL, 0}
};
const int main_menu_size = sizeof(main_menu) / sizeof(MenuItem);

// ==== Application Menu Entry Point ====
void app_menu_run(void)
{
    terminal_settings_reset_all();  // Ensure settings are reset on every start
    terminal_settings_apply();
    menu_manager_run("Main Menu", main_menu, main_menu_size);
}
