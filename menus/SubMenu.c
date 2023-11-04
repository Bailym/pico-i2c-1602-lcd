#include "SubMenu.h"
#include "scroll-menu.h"
#include "pico/stdlib.h"
#include "MainMenu.h"

tScrollMenu subMenu;

tScrollMenuItem subMenuItems[] =
    {
        {0, "Sub Menu Item 1", NULL},
        {1, "Sub Menu Item 2", NULL},
        {2, "Sub Menu Item 3", NULL},
        {3, "Back", MainMenu_Draw},
};

static const int subMenuItemsCount = sizeof(subMenuItems) / sizeof(subMenuItems[0]);

void SubMenu_Draw()
{
    InitMenu(&subMenu, subMenuItems, subMenuItemsCount);
}

void SubMenu_Scroll(tScrollDirection scrollDirection)
{
    ScrollMenu(&subMenu, scrollDirection);
}

void SubMenu_Select()
{
    SelectMenuItem(&subMenu);
}