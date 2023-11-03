#ifndef SCROLL_MENU_H
#define SCROLL_MENU_H

typedef struct
{
    int itemIndex;
    char *itemText;
} tScrollMenuItem;

typedef struct
{
    int itemCount;
    tScrollMenuItem *menuItems;
    int selectedItemIndex;
} tScrollMenu;

typedef enum
{
    SCROLL_UP,
    SCROLL_DOWN
} tScrollDirection;

void InitMenu(tScrollMenu *newScrollMenu, tScrollMenuItem menuItems[], int itemCount);
void ScrollMenu(tScrollMenu *scrollMenu, tScrollDirection scrollDirection);

#endif
