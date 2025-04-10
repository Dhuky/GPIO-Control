#ifndef __MAIN_HPP_
#define __MAIN_HPP_

#include "gpio_ctrl.hpp"

constexpr char TAG[] = "MAIN";

#define LED_PIN GPIO_NUM_2
#define BUTTON_PIN GPIO_NUM_4

void monitorButtonTask(void* pvParameters);

#endif // __MAIN_HPP__