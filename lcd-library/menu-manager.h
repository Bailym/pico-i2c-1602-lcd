#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

typedef struct
{
    int itemIndex;
    char *itemText;
    void (*onThisItemSelected)(void);
} tScrollMenuItem;

typedef struct
{
    int itemCount;
    tScrollMenuItem *menuItems;
    int selectedItemIndex;
    void(*onMenuDrawn)(void);
    void(*onMenuScrolled)(void);
    void(*onMenuItemSelected)(void);
} tScrollMenu;

typedef enum
{
    SCROLL_UP,
    SCROLL_DOWN
} tScrollDirection;

void MenuManager_DrawMenu(tScrollMenu *scrollMenu);
void MenuManager_ScrollMenu(tScrollMenu *scrollMenu, tScrollDirection scrollDirection);
void MenuManager_SelectMenuItem(tScrollMenu *scrollMenu);

#endif
