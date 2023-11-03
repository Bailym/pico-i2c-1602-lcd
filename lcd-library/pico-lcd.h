#ifndef PICO_LCD_H
#define PICO_LCD_H

#include "pico/stdlib.h"

typedef enum
{
    LCD_COMMAND = 0,
    LCD_CHARACTER = 1
} tByteMode;

void lcd_send_byte(uint8_t byteValue, tByteMode byteMode);
void lcd_clear(void);
void lcd_set_cursor(int lineNumber, int linePosition);
void lcd_char(char character);
void lcd_string(const char *stringPtr);
void lcd_init(void);
void lcd_write_multi_screen_message(char *messageToWrite[], int delayBetweenScreens);
void lcd_write_two_line_message(char *messageToWrite[2]);
void lcd_write_one_line_message(char *messageToWrite, int lineNumber);

#endif