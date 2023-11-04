#include "scroll-menu.h"
#include "pico-lcd.h"

void RedrawMenu(tScrollMenu *scrollMenu)
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

void InitMenu(tScrollMenu *newScrollMenu, tScrollMenuItem menuItems[], int itemCount)
{
    newScrollMenu->itemCount = itemCount;
    newScrollMenu->menuItems = menuItems;
    newScrollMenu->selectedItemIndex = 0;
    RedrawMenu(newScrollMenu);
}

void ScrollMenu(tScrollMenu *scrollMenu, tScrollDirection scrollDirection)
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

    RedrawMenu(scrollMenu);
}

void SelectMenuItem(tScrollMenu *scrollMenu)
{
    int selectedMenuItemIndex = scrollMenu->selectedItemIndex;
    tScrollMenuItem *selectedMenuItem = &scrollMenu->menuItems[selectedMenuItemIndex];

    if (selectedMenuItem->onSelect != NULL)
    {
        selectedMenuItem->onSelect();
    }
}
