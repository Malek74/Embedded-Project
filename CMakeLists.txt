# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)



# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

#include the FreeRTOS
include(C:/Malek/blink/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

# Initialize the Pico SDK
pico_sdk_init()



# Add the executable and source files
add_executable(${PROJECT_NAME}
    src/main.c                 # Main program source file
    drivers/led.c              # LED driver
    drivers/gyroscope.c        # Gyroscope driver
    drivers/infrared_sensor.c  # Infrared sensor driver
    drivers/LCD_DRIVER.c       # LCD driver
    drivers/motor_driver.c     # Motor driver
    drivers/ultrasonic_driver.c # Ultrasonic sensor driver
    drivers/bluetooth_module.c # Bluetooth module driver

)

# Link necessary libraries
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib             # Standard library for Pico
    hardware_i2c            # I2C support
    hardware_adc            # ADC support
    hardware_pwm            # PWM support

    pico_multicore          # Multicore support
    FreeRTOS-Kernel         # FreeRTOS Kernel
    FreeRTOS-Kernel-Heap4   # FreeRTOS Heap4
)

# Include directories for header files
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}  # Current directory
    ${CMAKE_CURRENT_LIST_DIR}   # Current list directory
    drivers             # Drivers directory 
  
)

# Enable extra output formats
pico_add_extra_outputs(${PROJECT_NAME})

# Enable USB for debug output and disable UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

