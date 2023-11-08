#include "menu-manager.h"
#include "pico-lcd.h"

static void DrawCurrentAndNextMenuItems(tScrollMenu *scrollMenu)
{
    int selectedMenuItemIndex = scrollMenu->selectedItemIndex;
    char *selectedMenuItemText = scrollMenu->menuItems[selectedMenuItemIndex].itemText;
    lcd_write_one_line_message(">", 0, LEFT_ALIGN);
    lcd_write_one_line_message(selectedMenuItemText, 0, LEFT_ALIGN_MENU_SELECTED_ITEM);

    int nextMenuItemIndex = selectedMenuItemIndex + 1;
    if (nextMenuItemIndex == scrollMenu->itemCount)
    {
        nextMenuItemIndex = 0;
    }

    char *nextMenuItemText = scrollMenu->menuItems[nextMenuItemIndex].itemText;
    lcd_write_one_line_message(nextMenuItemText, 1, LEFT_ALIGN);
}

static void CallSpecificDrawMenuFunctionIfSet(tScrollMenu *scrollMenu)
{
    if (scrollMenu->onMenuDrawn != NULL)
    {
        scrollMenu->onMenuDrawn();
    }
}

void MenuManager_DrawMenu(tScrollMenu *scrollMenu)
{
    lcd_clear();
    DrawCurrentAndNextMenuItems(scrollMenu);
    CallSpecificDrawMenuFunctionIfSet(scrollMenu);
}

static void ScrollMenuInGivenDirection(tScrollMenu *scrollMenu, tScrollDirection scrollDirection)
{
    if (scrollDirection == SCROLL_DOWN)
    {
        bool isLastItem = scrollMenu->selectedItemIndex == scrollMenu->itemCount - 1;

        if (isLastItem)
        {
            scrollMenu->selectedItemIndex = 0;
        }
        else
        {
            scrollMenu->selectedItemIndex++;
        }
    }
    else
    {
        bool isFirstItem = scrollMenu->selectedItemIndex == 0;

        if (isFirstItem)
        {
            scrollMenu->selectedItemIndex = scrollMenu->itemCount - 1;
        }
        else
        {
            scrollMenu->selectedItemIndex--;
        }
    }
}

static void CallSpecificScrollMenuFunctionIfSet(tScrollMenu *scrollMenu)
{
    if (scrollMenu->onMenuScrolled != NULL)
    {
        scrollMenu->onMenuScrolled();
    }
}

void MenuManager_ScrollMenu(tScrollMenu *scrollMenu, tScrollDirection scrollDirection)
{
    ScrollMenuInGivenDirection(scrollMenu, scrollDirection);
    CallSpecificScrollMenuFunctionIfSet(scrollMenu);
    MenuManager_DrawMenu(scrollMenu);
}

void CallSpecificOnMenuItemSelectedFunctionsIfSet(tScrollMenu *scrollMenu, tScrollMenuItem *selectedMenuItem)
{

    if (selectedMenuItem->onThisItemSelected != NULL)
    {
        selectedMenuItem->onThisItemSelected();
    }

    if (scrollMenu->onMenuItemSelected != NULL)
    {
        scrollMenu->onMenuItemSelected();
    }
}

void MenuManager_SelectMenuItem(tScrollMenu *scrollMenu)
{
    int selectedMenuItemIndex = scrollMenu->selectedItemIndex;
    tScrollMenuItem *selectedMenuItem = &scrollMenu->menuItems[selectedMenuItemIndex];
    CallSpecificOnMenuItemSelectedFunctionsIfSet(scrollMenu, selectedMenuItem);
}
