#ifndef __GPIO_CTRL_HPP__
#define __GPIO_CTRL_HPP__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

/**
 * @brief Class for GPIO control.
 *
 * This class provides an abstraction layer for handling GPIOs in the ESP-IDF framework.
 * It supports configuring pins as input or output, toggling their states, and reading
 * their digital levels.
 */
class GPIOControl {
private:
    static const char* TAG; ///< Tag used for logging within this class.
    
    gpio_num_t pin;  ///< GPIO pin number associated with this instance.
    
public:
    /**
     * @brief Constructor for initializing the GPIO control.
     * 
     * @param gpioPin The GPIO pin number.
     * @param mode The mode of the GPIO (e.g., input or output).
     * @param pullup Pull-up resistor configuration (default: disabled).
     * @param pulldown Pull-down resistor configuration (default: disabled).
     */
    GPIOControl(gpio_num_t gpioPin, gpio_mode_t mode, 
        gpio_pullup_t pullup = GPIO_PULLUP_DISABLE, 
        gpio_pulldown_t pulldown = GPIO_PULLDOWN_DISABLE);
    
    /**
     * @brief Sets the GPIO pin to HIGH.
     */
    void up();
    
    /**
     * @brief Sets the GPIO pin to LOW.
     */
    void down();
    
    /**
     * @brief Blinks the GPIO pin a specified number of times.
     * 
     * @param blinkTimeMs Time in milliseconds for each blink (HIGH + LOW).
     * @param times Number of times the GPIO pin will blink.
     */
    void blink(int blinkTimeMs, int times);
    
    /**
     * @brief Reads the digital state of the GPIO pin.
     * 
     * @return The digital state of the GPIO pin (0 = LOW, 1 = HIGH).
     */
    int read();
};
    

#endif // __GPIO_CTRL_HPP__
