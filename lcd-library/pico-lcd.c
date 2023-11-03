#include <stdio.h>
#include <string.h>
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico-lcd.h"

/*
   Connections on Raspberry Pi Pico W board

   GPIO 4 (pin 6)-> SDA on LCD
   GPIO 5 (pin 7)-> SCL on LCD
   VSYS (pin 39) -> VCC on LCD
   GND (pin 23)  -> GND on LCD
*/

// commands from the HD44780 datasheet --------------------------------------------------------

const int LCD_CLEARDISPLAY = 0x01;
const int LCD_RETURNHOME = 0x02;
const int LCD_INITIALISE8BITMODE = 0x03;
const int LCD_ENTRYMODESET = 0x04;
const int LCD_DISPLAYCONTROL = 0x08;
const int LCD_CURSORSHIFT = 0x10;
const int LCD_FUNCTIONSET = 0x20;
const int LCD_SETCGRAMADDR = 0x40;
const int LCD_SETDDRAMADDR = 0x80;

// Accompanying flags for each command from the HD44780 datasheet -----------------------------

// display entry mode
const int LCD_ENTRYSHIFTINCREMENT = 0x01;
const int LCD_ENTRYLEFT = 0x02;

// display and cursor control
const int LCD_BLINKON = 0x01;
const int LCD_CURSORON = 0x02;
const int LCD_DISPLAYON = 0x04;

// display and cursor shift
const int LCD_MOVERIGHT = 0x04;
const int LCD_DISPLAYMOVE = 0x08;

// function set
const int LCD_5x10DOTS = 0x04;
const int LCD_2LINE = 0x08;
const int LCD_8BITMODE = 0x10;

// --------------------------------------------------------------------------------------------

// backlight control bits
const int LCD_BACKLIGHT = 0x08;
const int LCD_ENABLE_BIT = 0x04;

// LCD display is usually on bus address 0x27 of 0x3F
static const int i2cBusAddress = 0x3F;

#define MAX_LINES 2
#define MAX_CHARS 16

// Write a byte to the I2C bus
static void i2c_write_byte(uint8_t byteValue)
{
#ifdef i2c_default
    bool noStopFlag = true;
    const uint8_t numberOfBytes = 1;
    i2c_write_blocking(i2c_default, i2cBusAddress, &byteValue, numberOfBytes, noStopFlag);
#endif
}

/*
    Send a byte of data, toggling the enable pin to create a pulse. This notifys the LCD that there is datya to be read.
    The LCD controller reads the data when the "enable" pulse (bit) transitions from high to low.
*/
static void lcd_toggle_enable_bit(uint8_t byteValue)
{
    const int DELAY_US = 600;

    sleep_us(DELAY_US);
    i2c_write_byte(byteValue | LCD_ENABLE_BIT); // Make sure the enable bit is set
    sleep_us(DELAY_US);
    i2c_write_byte(byteValue & ~LCD_ENABLE_BIT); // Make sure the enable bit is cleared
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t byteValue, tByteMode byteMode)
{
    uint8_t highNibble = byteMode | (byteValue & 0xF0) | LCD_BACKLIGHT;       // Send the high nibble first with the mode and backlight bits set
    uint8_t lowNibble = byteMode | ((byteValue << 4) & 0xF0) | LCD_BACKLIGHT; // Send the low nibble second with the mode and backlight bits set

    lcd_toggle_enable_bit(highNibble);
    lcd_toggle_enable_bit(lowNibble);
}

void lcd_clear(void)
{
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int lineNumber, int linePosition)
{
    int firstLineStartAddress = 0x80;
    int secondLineStartAddress = 0xC0;

    switch (lineNumber)
    {
    case 0:
        lcd_send_byte(firstLineStartAddress + linePosition, LCD_COMMAND);
        break;
    case 1:
        lcd_send_byte(secondLineStartAddress + linePosition, LCD_COMMAND);
        break;
    default:
        break;
    }
}

void lcd_char(char character)
{
    lcd_send_byte(character, LCD_CHARACTER);
}

void lcd_string(const char *stringPtr)
{
    while (*stringPtr)
    {
        lcd_char(*stringPtr++);
    }
}

void lcd_init()
{
    lcd_send_byte(LCD_INITIALISE8BITMODE, LCD_COMMAND);
    lcd_send_byte(LCD_INITIALISE8BITMODE, LCD_COMMAND);
    lcd_send_byte(LCD_INITIALISE8BITMODE, LCD_COMMAND);
    lcd_send_byte(LCD_RETURNHOME, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

static void set_cursor_for_alignment(int messageLength, int lineNumber, tTextAlignment textAlignment)
{
    switch (textAlignment)
    {
    case LEFT_ALIGN:
        lcd_set_cursor(lineNumber, 0);
        break;
    case CENTER_ALIGN:
        lcd_set_cursor(lineNumber, (MAX_CHARS - messageLength) / 2);
        break;
    case RIGHT_ALIGN:
        lcd_set_cursor(lineNumber, MAX_CHARS - messageLength);
        break;
    case LEFT_ALIGN_MENU_SELECTED_ITEM:
        lcd_set_cursor(lineNumber, 1);
        break;
    default:
        break;
    }
}

void lcd_write_multi_screen_message(char *messageToWrite[], int messageSize, int delayBetweenScreens, tTextAlignment textAlignment)
{
    // Take two strings at a time from the messageToWrite array
    for (int i = 0; i < messageSize; i += MAX_LINES)
    {
        // Go through each line on the LCD
        for (int lineNumber = 0; lineNumber < MAX_LINES; lineNumber++)
        {
            char *currentLineText = messageToWrite[i + lineNumber];
            int currentLineMessageLength = strlen(currentLineText);
            set_cursor_for_alignment(currentLineMessageLength, lineNumber, textAlignment);
            lcd_string(currentLineText);
        }
        sleep_ms(delayBetweenScreens);
        lcd_clear();
    }
}

void lcd_write_two_line_message(char *messageToWrite[2], tTextAlignment textAlignment)
{
    lcd_clear();

    for (int lineNumber = 0; lineNumber < MAX_LINES; lineNumber++)
    {
        char *currentLineText = messageToWrite[lineNumber];
        int currentLineMessageLength = strlen(currentLineText);
        set_cursor_for_alignment(currentLineMessageLength, lineNumber, textAlignment);
        lcd_string(currentLineText);
    }
}

void lcd_write_one_line_message(char *messageToWrite, int lineNumber, tTextAlignment textAlignment)
{
    int messageLength = strlen(messageToWrite);
    set_cursor_for_alignment(messageLength, lineNumber, textAlignment);
    lcd_string(messageToWrite);
}
