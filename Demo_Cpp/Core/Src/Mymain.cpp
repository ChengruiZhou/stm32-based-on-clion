//
// Created by Mr.zhou on 2024-07-28.
//
#include "Mymain.h"

LED led;

void Mymain(void){
    while (1)
    {
        led.LED_Off();
        HAL_Delay(1000);
        led.LED_ON();
        HAL_Delay(1000);
    }
}