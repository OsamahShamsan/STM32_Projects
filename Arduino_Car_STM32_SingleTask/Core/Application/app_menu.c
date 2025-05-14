#include "app_menu.h"
#include "menu_system.h"
#include "bsp_uart.h"

// Internal declarations
static void led_menu(void);
static void info_menu(void);
static void quit_menu(void);
static void led_toggle_action(void);
static void show_board_info(void);
static void show_firmware_version(void);

// Main Menu Table
static const MenuItem main_menu[] = {
    {'1', "LED Control", led_menu},
    {'2', "System Info", info_menu},
    {'q', "Quit", quit_menu}
};

// Sub Menus Table
const MenuItem led_menu_items[] = {
    {'1', "Toggle LED", led_toggle_action},
    {'b', "Back", NULL}
};

static const MenuItem info_menu_items[] = {
    {'1', "Board Info", show_board_info},
    {'2', "Firmware Version", show_firmware_version},
    {'b', "Back", NULL}
};

// Public function
void app_menu_run(void)
{
    menu_run("BIOS Style Dynamic Menu", main_menu, sizeof(main_menu) / sizeof(MenuItem));
}

// LED Submenu and actions (static = internal only)
static void led_toggle_action(void)
{
    bsp_uart_send("\r\n[LED] Toggled\r\n");
}



static void led_menu(void)
{
    menu_run("LED Control Menu", led_menu_items, sizeof(led_menu_items) / sizeof(MenuItem));
}

// Info Submenu and actions
static void show_board_info(void)
{
    bsp_uart_send("\r\nBoard: Nucleo G431RB\r\n");
}

static void show_firmware_version(void)
{
    bsp_uart_send("\r\nFirmware: v1.0.0\r\n");
}



static void info_menu(void)
{
    menu_run("System Info Menu", info_menu_items, sizeof(info_menu_items) / sizeof(MenuItem));
}

// Quit action
static void quit_menu(void)
{
    bsp_uart_send("\r\nExiting BIOS Menu.\r\n");
    while (1) {}
}
