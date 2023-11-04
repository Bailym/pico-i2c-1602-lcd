cmake_minimum_required(VERSION 3.12) # Require CMake 3.12 or newer

# Directory variables
set(I2C_DIR i2c/)
set(LCD_LIBRARY_DIR lcd-library/)
set(MENUS_DIR menus/)

# Include the Pico SDK CMake configuration
include(pico_sdk_import.cmake)

# Set the name and board for the project
set(PICO_BOARD 
    pico_w)

project(PICO-LCD)

# Initialize the Pico SDK
pico_sdk_init()

# Add executable target
add_executable(PICO_I2C_1602_LCD_EXECUTABLE 
    ${PROJECT_SOURCE_DIR}/main.c
    ${LCD_LIBRARY_DIR}/pico-lcd.c
    ${LCD_LIBRARY_DIR}/scroll-menu.c
    ${I2C_DIR}/i2c.c
    ${MENUS_DIR}/MainMenu.c
    ${MENUS_DIR}/SubMenu.c)


# Directories to include in build
include_directories(${I2C_DIR})
include_directories(${LCD_LIBRARY_DIR})
include_directories(${MENUS_DIR})

# Pull in external dependencies and additional I2C hardware support
target_link_libraries(PICO_I2C_1602_LCD_EXECUTABLE 
    pico_stdlib 
    hardware_i2c)

# Create map/bin/hex file, etc.
pico_add_extra_outputs(PICO_I2C_1602_LCD_EXECUTABLE)

