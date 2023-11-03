cmake_minimum_required(VERSION 3.12) # Require CMake 3.12 or newer

# Directory variables
set(I2C_DIR i2c/)
set(LCD_LIBRARY_DIR lcd-library/)

# Include the Pico SDK CMake configuration
include(pico_sdk_import.cmake)

# Set the name and board for the project
set(PICO_BOARD 
    pico_w)

project(PICO-LCD)

# Initialize the Pico SDK
pico_sdk_init()

# Add executable target
add_executable(MAIN_EXECUTABLE 
    ${PROJECT_SOURCE_DIR}/main.c
    ${LCD_LIBRARY_DIR}/pico-lcd.c
    ${I2C_DIR}/i2c.c)

# Directories to include in build
include_directories(${I2C_DIR})
include_directories(${LCD_LIBRARY_DIR})

# Pull in external dependencies and additional I2C hardware support
target_link_libraries(MAIN_EXECUTABLE 
    pico_stdlib 
    hardware_i2c)

# Create map/bin/hex file, etc.
pico_add_extra_outputs(MAIN_EXECUTABLE)

