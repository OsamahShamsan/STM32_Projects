#ifndef MENU_ITEM_H_
#define MENU_ITEM_H_

typedef struct MenuItem
{
    char key;
    const char* description;
    const char* (*action)(void);
    const struct MenuItem* submenu;
    int submenu_size;
} MenuItem;

#endif // MENU_ITEM_H_
