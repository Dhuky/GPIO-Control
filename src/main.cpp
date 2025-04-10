#include "main.hpp"

/**
 * @brief Main entry point for the ESP-IDF application.
 * 
 * This application demonstrates the use of the GPIOControl class for two purposes:
 * 1. Controlling a GPIO pin configured as an output (LED).
 * 2. Monitoring a GPIO pin configured as an input (button).
 *
 * The program runs two tasks:
 * - The main task controls the LED with blinking and toggling logic.
 * - A separate FreeRTOS task monitors the button state and logs its status.
 */
extern "C" void app_main() 
{
    // Initialize GPIOControl object for LED (output pin)
    GPIOControl led(LED_PIN, GPIO_MODE_OUTPUT);

    // Create a FreeRTOS task to monitor the button state in parallel
    xTaskCreate(monitorButtonTask, "MonitorButtonTask", 2048, NULL, 1, NULL );

    // Main loop for LED control
    while (true) 
    {
        // Blink the LED 5 times, 1 second per blink
        ESP_LOGI(TAG, "Start LED blink mode...");
        led.blink(1000, 5);
    
        // Turn off the LED and wait for 2 seconds
        ESP_LOGI(TAG, "LED down");
        led.down();
        vTaskDelay(2000 / portTICK_PERIOD_MS);

        // Turn on the LED and wait for 2 seconds
        ESP_LOGI(TAG, "LED up");
        led.up();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief FreeRTOS task to monitor the state of a button.
 * 
 * This task periodically reads the digital state of the button GPIO pin and logs its status.
 * The pin is configured as an input with a pull-up resistor enabled.
 * 
 * @param pvParameters Task parameters (unused in this case).
 */
void monitorButtonTask(void* pvParameters) 
{
    // Initialize GPIOControl object for button (input pin)
    GPIOControl button(BUTTON_PIN, GPIO_MODE_INPUT, GPIO_PULLUP_ENABLE);

    while (true) 
    {
        // Read the digital state of the button (HIGH or LOW)
        int state = button.read();

        // Log the state of the button
        if (state) {
            ESP_LOGI("ButtonMonitor", "Button pressed (HIGH)");
        } else {
            ESP_LOGI("ButtonMonitor", "Button released (LOW)");
        }

        // Delay to avoid excessive reading
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
