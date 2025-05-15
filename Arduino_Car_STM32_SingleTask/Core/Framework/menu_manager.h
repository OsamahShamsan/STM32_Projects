#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

// Maximum supported menu depth for breadcrumbs (optional)
#define MAX_BREADCRUMB_DEPTH 5
#define MAX_BREADCRUMB_NAME  32

// Structure for a menu item
typedef struct MenuItem MenuItem;

struct MenuItem {
    char key;                        // Key that the user must press (e.g., '1', 'q')
    const char *description;         // Description shown in the menu
    const char* (*action)(void);     // Function pointer to action (could be NULL)
    const MenuItem *submenu;         // Pointer to submenu	(could be NULL)
    int submenu_size;                // Size of the submenu table
};

// Core function to start the menu system
void menu_run(const char *title, const MenuItem *menu_table, int menu_size);

#endif // MENU_SYSTEM_H_
