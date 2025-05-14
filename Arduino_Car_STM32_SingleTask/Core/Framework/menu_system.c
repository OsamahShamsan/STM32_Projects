#include "menu_system.h"
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
        for (int i = 0; i < menu_size; i++)
        {
            char line[64];
            sprintf(line, "%c. %s\r\n", menu_table[i].key, menu_table[i].description);
            bsp_uart_send(line);
        }
        bsp_uart_send("Select option: ");

        option = bsp_uart_receive_char();

        // Search table
        int found = 0;
        for (int i = 0; i < menu_size; i++)
        {
            if (option == menu_table[i].key)
            {
                // ✔ If NULL action, treat it as 'Back'
                if (menu_table[i].action == NULL)
                    return;

                menu_table[i].action();  // Call the handler
                found = 1;
                break;
            }
        }

        if (!found)
        {
            bsp_uart_send("\r\nInvalid option.\r\n");
        }

        // ✔ Always pause after any action so user can see the output before screen clears
        bsp_uart_send("\r\nPress any key to continue...\r\n");
        bsp_uart_receive_char();
    }
}
