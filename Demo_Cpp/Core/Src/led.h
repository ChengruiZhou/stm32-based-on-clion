//
// Created by Mr.zhou on 2024-07-28.
//

#ifndef STM32H743_LED_H
#define STM32H743_LED_H

class LED{
public:
    enum LED_status{
        off = 0,
        on
    };
    void LED_ON();
    void LED_Off();
};

void Mymain(void);

#endif //STM32H743_LED_H
