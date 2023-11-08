#include "MainMenu.h"
#include "TestScreen.h"
#include "pico/stdlib.h"
#include "screen-manager.h"

static void SelectAdjustNumber()
{
    ScreenManager_InitScreen(&testScreen);
}

static tScrollMenuItem mainMenuItems[] =
    {
        {0, "Menu Item 1", NULL},
        {1, "Menu Item 2", NULL},
        {2, "Menu Item 3", NULL},
        {3, "Adjust Number", SelectAdjustNumber},
};

static const int mainMenuItemsCount = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

tScrollMenu mainMenu = {
    .itemCount = mainMenuItemsCount,
    .menuItems = mainMenuItems,
    .selectedItemIndex = 0,
    .onMenuDrawn = NULL,
    .onMenuScrolled = NULL,
    .onMenuItemSelected = NULL
};


