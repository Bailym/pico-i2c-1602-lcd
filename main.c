#include "i2c.h"
#include "pico-lcd.h"
#include "scroll-menu.h"
#include "hardware/i2c.h"

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

    tScrollMenuItem menuItems[] =
        {
            {0, "Menu Item 1"},
            {1, "Menu Item 2"},
            {2, "Menu Item 3"},
            {3, "Menu Item 4"},
        };

    tScrollMenu scrollMenu;
    InitMenu(&scrollMenu, menuItems, 4);

    while (1)
    {
        ScrollMenu(&scrollMenu, SCROLL_UP);
        sleep_ms(1000);
    }

#endif
}