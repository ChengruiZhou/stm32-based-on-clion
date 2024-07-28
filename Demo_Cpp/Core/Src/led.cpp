//
// Created by Mr.zhou on 2024-07-28.
//

#include "led.h"
#include "main.h"

void LED::LED_ON() {
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
}

void LED::LED_Off() {
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
}
