#include "MainMenu.h"
#include "TestScreen.h"
#include "scroll-menu.h"
#include "pico/stdlib.h"
#include "screen-manager.h"

static void MainMenu_SelectItemFour();

static tScrollMenu mainMenu;

static tScrollMenuItem mainMenuItems[] =
    {
        {0, "Menu Item 1", NULL},
        {1, "Menu Item 2", NULL},
        {2, "Menu Item 3", NULL},
        {3, "Adjust Number", MainMenu_SelectAdjustNumber},
};

static const int mainMenuItemsCount = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

void MainMenu_Draw()
{
    InitMenu(&mainMenu, mainMenuItems, mainMenuItemsCount);
}

void MainMenu_Scroll(tScrollDirection scrollDirection)
{
    ScrollMenu(&mainMenu, scrollDirection);
}

void MainMenu_Select()
{
    SelectMenuItem(&mainMenu);
}

static void MainMenu_SelectAdjustNumber()
{
    ScreenManager_InitScreen(&testScreen);
}

