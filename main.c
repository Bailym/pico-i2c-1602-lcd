#include "i2c.h"
#include "pico-lcd.h"
#include "hardware/i2c.h"

int main()
{
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    setup_i2c_gpio();
    lcd_init();

    char *messageToWrite[] = {
        "RP2040 by", "Raspberry Pi",
        "A brand new", "microcontroller",
        "Twin core M0", "Full C SDK"};

    int messageSize = sizeof(messageToWrite) / sizeof(messageToWrite[0]);
    int messageShowTimeMs = 5000;

    char* lineOneMessage = "line 1";
    char* lineTwoMessage = "line 2";

    lcd_write_one_line_message(lineOneMessage,0);
    lcd_write_one_line_message(lineTwoMessage,1);
#endif
}