#include "menu-manager.h"
#include "pico-lcd.h"

void MenuManager_DrawMenu(tScrollMenu *scrollMenu)
{
    lcd_clear();
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

void MenuManager_ScrollMenu(tScrollMenu *scrollMenu, tScrollDirection scrollDirection)
{
    if (scrollDirection == SCROLL_DOWN)
    {
        if (scrollMenu->selectedItemIndex == scrollMenu->itemCount - 1)
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
        if (scrollMenu->selectedItemIndex == 0)
        {
            scrollMenu->selectedItemIndex = scrollMenu->itemCount - 1;
        }
        else
        {
            scrollMenu->selectedItemIndex--;
        }
    }

    MenuManager_DrawMenu(scrollMenu);
}

void MenuManager_SelectMenuItem(tScrollMenu *scrollMenu)
{
    int selectedMenuItemIndex = scrollMenu->selectedItemIndex;
    tScrollMenuItem *selectedMenuItem = &scrollMenu->menuItems[selectedMenuItemIndex];

    if (selectedMenuItem->onSelect != NULL)
    {
        selectedMenuItem->onSelect();
    }
}
