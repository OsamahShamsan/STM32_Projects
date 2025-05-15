#include "menu_manager.h"
#include "bsp_uart.h"
#include "vt100.h"
#include <stdio.h>
#include <string.h>

void menu_run(const char *title, const MenuItem *menu_table, int menu_size)
{
    char option = 0;

    while (1)
    {
        vt100_clear_screen();
        bsp_uart_send(title);
        bsp_uart_send("\r\n========================\r\n");

        // print the menu or submenu
        for (int i = 0; i < menu_size; i++)
        {
            char line[64];
            sprintf(line, "%c. %s\r\n", menu_table[i].key, menu_table[i].description);
            bsp_uart_send(line);
        }

        bsp_uart_send("\r\nSelect option: ");

        // Blocking reading
        option = bsp_uart_receive_char();

        int found = 0;

        // Loop through the indexes of a menu or a submenu
        for (int i = 0; i < menu_size; i++)
        {
        	// check in each loop if there is a matching key
            if (option == menu_table[i].key)
            {
            	// found = 1 means the input char by the user match a key in a menu or submenu (does not handle duplicated keys)
                found = 1;

                // Print the selected menu or submenu
                if (menu_table[i].submenu != NULL)
                {
                    menu_run(menu_table[i].description, menu_table[i].submenu, menu_table[i].submenu_size);
                }

                // In case there is no action to do
                else if (menu_table[i].action != NULL)
                {
                    menu_table[i].action();
                    bsp_uart_send("\r\nPress any key to continue...\r\n");
                    bsp_uart_receive_char();
                }
                // In case b is pressed 0 =>  NULL submenu and NULL action
                else
                {
                    return;
                }
                break;
            }
        }

        // In case any invalid char is entered
        if (!found)
        {
        	char msg[32];
        	sprintf(msg, "\r\n%c is Invalid option.\r\n", option);
        	bsp_uart_send(msg);

            bsp_uart_send("\r\nPress any key to continue...\r\n");
            bsp_uart_receive_char();
        }
    }
}
