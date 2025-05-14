#ifndef MENU_SYSTEM_H_
#define MENU_SYSTEM_H_

typedef struct {
    char key;                     // Key to trigger the action (e.g., '1')
    const char *description;      // Description shown in the menu
    void (*action)(void);         // Handler function pointer
} MenuItem;

void menu_run(const char *title, const MenuItem *menu_table, int menu_size);

#endif
