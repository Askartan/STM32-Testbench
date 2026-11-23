#include "app.h"
#include <stdint.h>

#define GPIOA_MODER (*(volatile uint32_t *)0x50000000UL)
#define GPIOC_MODER (*(volatile uint32_t *)0x50000800UL)
#define GPIOA_ODR   (*(volatile uint32_t *)0x50000014UL)
#define GPIOC_IDR   (*(volatile uint32_t *)0x50000810UL)
#define RCC_IOPENR  (*(volatile uint32_t *)0x40021034UL)

int main(void) {
    RCC_IOPENR |= (1UL << 0);
    RCC_IOPENR |= (1UL << 2);

    GPIOA_MODER &= ~(3UL << 10);
    GPIOA_MODER |=  (1UL << 10);       
    
    GPIOC_MODER &= ~(3UL << 26);
    
    AppState app = {
        .was_pressed = ((GPIOC_IDR & (1UL << 13)) == 0UL),
        .led_on = ((GPIOA_ODR ^= (1UL << 5)) != 0UL)
    };

    while (1) {
        bool pressed = ((GPIOC_IDR & (1UL << 13)) == 0UL);
        app_update(&app, pressed);
        
        if (app.led_on) {
            GPIOA_ODR |= (1UL << 5);
        } else if (!app.led_on) {
            GPIOA_ODR &= ~(1UL << 5);
        } 
    }
}


