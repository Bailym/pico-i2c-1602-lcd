# pico-i2c-1602-lcd
A simple C library for a 16-character 2-line LCD. Based on the following example library from Raspberry Pi: https://github.com/raspberrypi/pico-examples/tree/master/i2c/lcd_1602_i2c

## Features

- Single-line, two-line, and multi-screen text drawing.
- Customisable scrollable menus.
- Assignable onMenuDrawn, onMenuScrolled, and onMenuItemSelected functions.
- Assignable screenInit, screenExit, screenSelect, screenScrollUp, screenScrollDown functions.
- Basic examples.

## Skills learned/developed with this project

- Low-level driver programming in C.
- I2C protocol implementation.
- Generic 1602 LCD functionality.
- Interpreting a data sheet and implementing behaviours based on it.
- Event-based callback functions.
- Screen and menu management architecture.  

## Basic Demonstration of what an interface using this library might look like

The GIF shows an example where:
- A 4-item menu is displayed.
- The menu is scrolled until the 'Adjust Number' menu item is highlighted.
- The 'Adjust Number' menu item is selected, showing the 'Test Screen'
- The number on the 'Test Screen' is incremented 5 times (e.g. by scrolling, or pressing a button)
- The number on the 'Test Screen' is reset to 0 (e.g. by pressing a button)
- The number on the 'Test Screen' is decremented 3 times (e.g. by scrolling, or pressing a button)

**Note that this library only covers the LCD implementation and not any buttons/encoders you might use to control the LCD.**

[https://github.com/Bailym/pico-i2c-1602-lcd/blob/main/examples/demo.gif](https://github.com/Bailym/pico-i2c-1602-lcd/blob/main/examples/demo.gif?raw=true)


