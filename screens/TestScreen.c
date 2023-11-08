#include "screen-manager.h"
#include "TestScreen.h"
#include "pico-lcd.h"
#include <stdio.h>

static int counter;

static void TestScreen_DrawScreenElements()
{
    char counterString[10];
    snprintf(counterString, sizeof(counterString), "%d", counter);

    lcd_write_one_line_message("Test Screen", 0, CENTER_ALIGN);
    lcd_write_one_line_message(counterString, 1, CENTER_ALIGN);
}

static void TestScreen_Select()
{
    counter = 0;
    TestScreen_DrawScreenElements();
}

static void TestScreen_ScrollUp()
{
    counter++;
    TestScreen_DrawScreenElements();
}

static void TestScreen_ScrollDown()
{
    counter--;
    TestScreen_DrawScreenElements();
}

static void TestScreen_Exit()
{
    lcd_clear();
    lcd_set_cursor(0, 0);
}

static void TestScreen_Init()
{
    counter = 0;
    
    lcd_clear();
    lcd_set_cursor(0, 0);
    TestScreen_DrawScreenElements();
}

tScreen testScreen = {
    .screenName = "Test Screen",
    .screenInit = TestScreen_Init,
    .screenExit = TestScreen_Exit,
    .screenSelect = TestScreen_Select,
    .screenScrollUp = TestScreen_ScrollUp,
    .screenScrollDown = TestScreen_ScrollDown
};

