#include "i2c.h"
#include "pico-lcd.h"
#include "menu-manager.h"
#include "hardware/i2c.h"
#include "MainMenu.h"
#include "TestScreen.h"
#include "screen-manager.h"

int main()
{

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    
    stdio_init_all();
    setup_i2c_gpio();
    lcd_init();

    MenuManager_DrawMenu(&mainMenu);

    while (1)
    {

    }


#endif
}