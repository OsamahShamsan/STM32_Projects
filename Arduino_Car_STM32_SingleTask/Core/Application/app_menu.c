#include "app_menu.h"
#include "bsp_gpio.h"
#include "vt100.h"

// ==== Application Actions (Logic & Result Reporting) ====
const char* led_toggle_action(void)
{
    bsp_gpio_toggle(GPIOA, GPIO_PIN_5);
    return "[LED] Toggled.";
}

const char* led_on_action(void)
{
    bsp_gpio_set(GPIOA, GPIO_PIN_5);
    return "[LED] ON.";
}

const char* show_board_info(void)
{
    return "Board: Nucleo G431RB";
}

const char* led_off_action(void)
{
    bsp_gpio_clear(GPIOA, GPIO_PIN_5);
    return "[LED] OFF.";
}

const char* show_firmware_version(void)
{
    return "Firmware Version: v1.0.0";
}

const char* quit_handler(void)
{
    return "Exiting BIOS Menu. (System Halted)";
}

const char* vt100_toggle_cursor(void)
{
    vt100_cursor_toggle();  // User-defined in vt100.c
    return "[Terminal] Cursor visibility toggled.";
}

const char* vt100_set_blue_text(void)
{
    vt100_set_text_color(VT100_BLUE);
    return "[Terminal] Text color set to BLUE.";
}

const char* vt100_set_default_style(void)
{
    vt100_reset_attributes();
    return "[Terminal] Reset to default style.";
}

// ==== Submenus ====
const MenuItem led_menu[] = {
    {'1', "Toggle LED", led_toggle_action, NULL, 0},
    {'2', "LED ON", led_on_action, NULL, 0},
    {'3', "LED OFF", led_off_action, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int led_menu_size = sizeof(led_menu) / sizeof(MenuItem);

const MenuItem info_menu[] = {
    {'1', "Board Info", show_board_info, NULL, 0},
    {'2', "Firmware Version", show_firmware_version, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int info_menu_size = sizeof(info_menu) / sizeof(MenuItem);

const MenuItem terminal_settings_menu[] = {
    {'1', "Toggle Cursor Visibility", vt100_toggle_cursor, NULL, 0},
    {'2', "Set Text Color to BLUE", vt100_set_blue_text, NULL, 0},
    {'3', "Reset to Default Style", vt100_set_default_style, NULL, 0},
    {'b', "Back", NULL, NULL, 0}
};
const int terminal_settings_menu_size = sizeof(terminal_settings_menu) / sizeof(MenuItem);

// ==== Main Menu ====
const MenuItem main_menu[] = {
    {'1', "LED Control", NULL, led_menu, led_menu_size},
    {'2', "System Info", NULL, info_menu, info_menu_size},
    {'3', "Terminal Settings", NULL, terminal_settings_menu, terminal_settings_menu_size},
    {'q', "Quit", quit_handler, NULL, 0}
};
const int main_menu_size = sizeof(main_menu) / sizeof(MenuItem);

// ==== Application Menu Entry Point ====
void app_menu_run(void)
{
    menu_run("Main Menu", main_menu, main_menu_size);
}
