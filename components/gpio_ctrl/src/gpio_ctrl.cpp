#include "gpio_ctrl.hpp"

const char* GPIOControl::TAG = "GPIO_CTRL";

GPIOControl::GPIOControl(gpio_num_t gpioPin, gpio_mode_t mode, gpio_pullup_t pullup, gpio_pulldown_t pulldown) : pin(gpioPin) 
{
    gpio_reset_pin(pin);

    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.mode = mode;
    io_conf.pull_up_en = pullup;
    io_conf.pull_down_en = pulldown;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    if (mode == GPIO_MODE_OUTPUT || mode == GPIO_MODE_OUTPUT_OD) {
    gpio_set_level(pin, 0);
    }
    ESP_LOGI(TAG, "GPIO %d configurado como %s", pin, mode == GPIO_MODE_OUTPUT ? "OUTPUT" : "INPUT");
}

void GPIOControl::up() 
{
    gpio_set_level(pin, 1);
}

void GPIOControl::down() 
{
    gpio_set_level(pin, 0); 
}

void GPIOControl::blink(int blinkTimeMs, int times) 
{
    for (int i = 0; i < times; i++) {
        this->up();
        vTaskDelay(pdMS_TO_TICKS(blinkTimeMs));
        this->down();
        vTaskDelay(pdMS_TO_TICKS(blinkTimeMs));
    }
}

int GPIOControl::read() 
{
    return gpio_get_level(pin);
}
