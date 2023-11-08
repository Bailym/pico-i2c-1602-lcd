#include "i2c.h"
#include "pico-lcd.h"
#include "scroll-menu.h"
#include "hardware/i2c.h"
#include "MainMenu.h"
#include "SubMenu.h"
#include "TestScreen.h"
#include "screen-manager.h"
#include <stdio.h>

int main()
{

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    
    stdio_init_all();
    setup_i2c_gpio();
    lcd_init();

    printf("Application started.\n");

    char *multiScreenMessage[] = {
        "This is a", "multi screen",
        "message", "with 4 lines"};

    int multiLineMessageSize = sizeof(multiScreenMessage) / sizeof(multiScreenMessage[0]);
    int screenShowTime = 1000;

    char *twoLineMessage[] = {"line 1", "line 2"};

    char *lineOneMessage = "line 1";
    char *lineTwoMessage = "line 2";

    MainMenu_Draw();

    while (1)
    {
        sleep_ms(1000);
        MainMenu_Scroll(SCROLL_DOWN);
        sleep_ms(1000);
        MainMenu_Scroll(SCROLL_DOWN);
        sleep_ms(1000);
        MainMenu_Scroll(SCROLL_DOWN);
        sleep_ms(1000);
        MainMenu_Select();

        ScreenManager_ScrollUp(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollUp(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollUp(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollUp(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollUp(&testScreen);
        sleep_ms(1000);
        ScreenManager_SelectPress(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollDown(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollDown(&testScreen);
        sleep_ms(1000);
        ScreenManager_ScrollDown(&testScreen);
        sleep_ms(1000);
        ScreenManager_ExitScreen(&testScreen);
    }

#endif
}