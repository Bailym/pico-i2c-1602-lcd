#include "i2c.h"
#include "pico-lcd.h"
#include "scroll-menu.h"
#include "hardware/i2c.h"

void DrawnMainMenu();
void DrawSubMenu();

tScrollMenu mainMenu = {};
tScrollMenu subMenu = {};

tScrollMenuItem mainMenuItems[] =
    {
        {0, "Menu Item 1", NULL},
        {1, "Menu Item 2", NULL},
        {2, "Menu Item 3", NULL},
        {3, "Go To Sub Menu", DrawSubMenu},
};

tScrollMenuItem subMenuItems[] =
    {
        {0, "Sub Menu Item 1", NULL},
        {1, "Sub Menu Item 2", NULL},
        {2, "Sub Menu Item 3", NULL},
        {3, "Back", DrawnMainMenu},
};

void DrawnMainMenu()
{
    InitMenu(&mainMenu, mainMenuItems, 4);
}

void DrawSubMenu()
{
    InitMenu(&subMenu, subMenuItems, 4);
}

int main()
{
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    setup_i2c_gpio();
    lcd_init();

    char *multiScreenMessage[] = {
        "This is a", "multi screen",
        "message", "with 4 lines"};

    int multiLineMessageSize = sizeof(multiScreenMessage) / sizeof(multiScreenMessage[0]);
    int screenShowTime = 1000;

    char *twoLineMessage[] = {"line 1", "line 2"};

    char *lineOneMessage = "line 1";
    char *lineTwoMessage = "line 2";

    DrawnMainMenu();

    while (1)
    {
        sleep_ms(1000);
        ScrollMenu(&mainMenu, SCROLL_DOWN);
        sleep_ms(1000);
        ScrollMenu(&mainMenu, SCROLL_DOWN);
        sleep_ms(1000);
        ScrollMenu(&mainMenu, SCROLL_DOWN);
        sleep_ms(1000);
        SelectMenuItem(&mainMenu);

        sleep_ms(1000);
        ScrollMenu(&subMenu, SCROLL_DOWN);
        sleep_ms(1000);
        ScrollMenu(&subMenu, SCROLL_DOWN);
        sleep_ms(1000);
        ScrollMenu(&subMenu, SCROLL_DOWN);
        sleep_ms(1000);
        SelectMenuItem(&subMenu);
    }

#endif
}