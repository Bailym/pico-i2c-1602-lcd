#include "screen-manager.h"
#include "pico-lcd.h" 

void ScreenManager_InitScreen(tScreen *screen)
{
    screen->screenInit();
}

void ScreenManager_ExitScreen(tScreen *screen)
{
    lcd_clear();
    lcd_set_cursor(0, 0);
    screen->screenExit();
}

void ScreenManager_SelectPress(tScreen *screen)
{
    screen->screenSelect();
}

void ScreenManager_ScrollUp(tScreen *screen)
{
    screen->screenScrollUp();
}

void ScreenManager_ScrollDown(tScreen *screen)
{
    screen->screenScrollDown();
}