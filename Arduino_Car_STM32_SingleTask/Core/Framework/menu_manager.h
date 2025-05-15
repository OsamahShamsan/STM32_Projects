#ifndef MENU_MANAGER_H_
#define MENU_MANAGER_H_

#include "menu_item.h"

extern char current_key;  // Export the key globally for app handlers

void menu_manager_run(const char* title, const MenuItem* menu, int menu_size);

#endif // MENU_MANAGER_H_
