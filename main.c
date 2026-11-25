#include "app.h"

//led
#define GPIOA_MODER (*(volatile uint32_t *)0x50000000UL)
#define GPIOA_ODR   (*(volatile uint32_t *)0x50000014UL)

//output GPIO
#define RCC_IOPENR  (*(volatile uint32_t *)0x40021034UL)

//guzik
#define GPIOC_MODER (*(volatile uint32_t *)0x50000800UL)
#define GPIOC_IDR   (*(volatile uint32_t *)0x50000810UL)

//systick
#define STK_CSR     (*(volatile uint32_t *)0xE000E010UL) 
#define STK_RVR     (*(volatile uint32_t *)0xE000E014UL) 
#define STK_CVR     (*(volatile uint32_t *)0xE000E018UL) 

//zmienne do systicka
#define COUNTFLAG   (STK_CSR & (1UL << 16))
#define CLOCK       (12000000)
#define SECOND      (CLOCK - 1)
#define MILLISECOND ((CLOCK / 1000) - 1)

#define PRESSED     ((GPIOC_IDR & (1UL << 13)) == 0UL)

int main(void) {
    
    // uruchamiam clock na gpio a (led) i c (guzik)
    RCC_IOPENR |= (1UL << 0);
    RCC_IOPENR |= (1UL << 2);
    
    // output na led
    GPIOA_MODER &= ~(3UL << 10);
    GPIOA_MODER |=  (1UL << 10);       
    
    // output na guziku
    GPIOC_MODER &= ~(3UL << 26);
    
    // config systick
    STK_CVR = 0UL; // reset timera
    STK_CSR |= (5UL); //uruchomienie paskudy
    STK_RVR = MILLISECOND;
    
    AppState app = {
        .stable_pressed = PRESSED,
        .raw_pressed = PRESSED,
        .was_pressed = PRESSED,
        .led_on = ((GPIOA_ODR & (1UL << 5)) != 0UL),
        .timer = 0
    };

    while (1) {
        bool pressed = PRESSED;
        
        if (COUNTFLAG) {
            ++app.timer;
        }
            
        app_update(&app, pressed, app.timer);
        
        if (app.led_on) {
            GPIOA_ODR |= (1UL << 5);
        } else if (!app.led_on) {
            GPIOA_ODR &= ~(1UL << 5);
        } 
    }
}

