#include "menu_manager.h"
#include "vt100_terminal.h"
#include "terminal_settings.h"
#include "app_menus.h"
#include <stdio.h>
#include <string.h>

char current_key = 0;

// Markers using font/background/styles from pending settings
static const char* get_marker_for_font_color(uint8_t color)
{
    if (terminal_settings_get_pending()->font_color == color)
        return " [✔]";
    return "";
}

static const char* get_marker_for_bg_color(uint8_t color)
{
    if (terminal_settings_get_pending()->background_color == color)
        return " [✔]";
    return "";
}

static const char* get_marker_for_style(uint8_t style)
{
    if (terminal_settings_get_pending()->styles & style)
        return " [✔]";
    return "";
}

// Simple key read
static char read_key(void)
{
    return vt100_terminal_read_char();
}

void menu_manager_run(const char* title, const MenuItem* menu, int menu_size)
{
    while (1)
    {
        vt100_terminal_clear_screen();
        vt100_terminal_write(title);
        vt100_terminal_write("\r\n==============================\r\n");

        for (int i = 0; i < menu_size; i++)
        {
            char line[64];

            if (menu == font_color_menu)
            {
                uint8_t color = menu[i].key - '1';  // Use clean mapping
                sprintf(line, "  %c. %s%s\r\n", menu[i].key, menu[i].description,
                        get_marker_for_font_color(color));
            }
            else if (menu == bg_color_menu)
            {
                uint8_t color = menu[i].key - '1';
                sprintf(line, "  %c. %s%s\r\n", menu[i].key, menu[i].description,
                        get_marker_for_bg_color(color));
            }
            else if (menu == font_style_menu)
            {
                uint8_t style = (menu[i].key == '1') ? STYLE_BOLD :
                                (menu[i].key == '2') ? STYLE_ITALIC :
                                (menu[i].key == '3') ? STYLE_UNDERLINE : 0;
                sprintf(line, "  %c. %s%s\r\n", menu[i].key, menu[i].description,
                        get_marker_for_style(style));
            }
            else
            {
                sprintf(line, "  %c. %s\r\n", menu[i].key, menu[i].description);
            }

            vt100_terminal_write(line);
        }

        vt100_terminal_write("\r\nSelect option: ");
        char key = read_key();

        char feedback[8];
        sprintf(feedback, "%c\r\n", key);
        vt100_terminal_write(feedback);

        current_key = key;

        int found = 0;
        for (int i = 0; i < menu_size; i++)
        {
            if (key == menu[i].key)
            {
                found = 1;
                if (menu[i].submenu != NULL)
                {
                    menu_manager_run(menu[i].description,
                                     menu[i].submenu,
                                     menu[i].submenu_size);
                }
                else if (menu[i].action != NULL)
                {
                    const char* result = menu[i].action();
                    if (result != NULL)
                    {
                        vt100_terminal_write("\r\n");

                        if (strncmp(result, "@EXIT@", 6) == 0)
                        {
                            vt100_terminal_write(result + 6);
                            vt100_terminal_write("\r\nPress any key to continue...\r\n");
                            vt100_terminal_read_char();
                            return;
                        }
                        else
                        {
                            vt100_terminal_write(result);
                            vt100_terminal_write("\r\nPress any key to continue...\r\n");
                            vt100_terminal_read_char();
                        }
                    }
                }
                else
                {
                    return;
                }
                break;
            }
        }

        if (!found)
        {
            char msg[64];
            sprintf(msg, "\r\n'%c' is Invalid option.\r\n", key);
            vt100_terminal_write(msg);
            vt100_terminal_write("\r\nPress any key to continue...\r\n");
            vt100_terminal_read_char();
        }
    }
}
