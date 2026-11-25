#ifndef UART_H
#define UART_H

// inicjalizuje UART, w tym niezbedne rejestry
void uart_init(void);

// wysyla jeden (1) znak
void uart_send_char(char c);

// wysyla znaki az do \0
void uart_send_string(const char *str);

#endif