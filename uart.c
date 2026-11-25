#include "uart.h"
#include <stdint.h>

//USART 
#define GPIOA_MODER (*(volatile uint32_t *)0x50000000UL)
#define GPIOA_AFRL  (*(volatile uint32_t *)0x50000020UL)
#define RCC_APBENR1 (*(volatile uint32_t *)0x4002103CUL)
#define USART2_CR1  (*(volatile uint32_t *)0x40004400UL)
#define USART2_BRR  (*(volatile uint32_t *)0x4000440CUL)
#define USART2_TDR  (*(volatile uint32_t *)0x40004428UL)
#define USART2_ISR  (*(volatile uint32_t *)0x4000441CUL)
#define USART_CLOCK_HZ 12000000UL
#define BAUD_RATE      115200UL

#define CAN_SEND    ((USART2_ISR & (1UL << 7)) != 0)

void uart_init(void) {
    // AF na PA2
    GPIOA_MODER &= ~(3UL << 4);
    GPIOA_MODER |=  (1UL << 5);
    
    // AF1 na PA2
    GPIOA_AFRL  &= ~(15UL << 8);
    GPIOA_AFRL  |=  (1UL << 8);
    
    // USART2 clock
    RCC_APBENR1 |=  (1UL << 17);
    
    // USART2 enable & transmitter
    USART2_BRR   =  USART_CLOCK_HZ / BAUD_RATE;
    USART2_CR1  |=  ((1UL) | (1UL << 3));
}
    

void uart_send_char(char c) {
    while (!CAN_SEND) {
    }
    
    USART2_TDR = c;
}