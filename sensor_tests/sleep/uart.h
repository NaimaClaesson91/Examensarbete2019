#ifndef UART_H
#define UART_H

#define BAUDRATE 9600
#define UBRR (F_CPU / 16 / BAUDRATE - 1)

void uart_init(void);

int uart_putchar(char chr, FILE * p_stream);

char uart_getchar(void);

#endif // UART_H

