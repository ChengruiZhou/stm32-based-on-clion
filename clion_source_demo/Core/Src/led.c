//
// Created by Mr.zhou on 2023/5/1.
//

#include "led.h"
#include "main.h"
void led_on(void){
    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,RESET);
}

void led_off(void){
    HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,SET);
}