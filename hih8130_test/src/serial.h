#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUDRATE 9600
#define UBRR (F_CPU/16/BAUDRATE-1)

void uart_init(void);

int uart_putchar(char chr, FILE *stream);

char uart_getchar(void);

void uart_putstr(const char *str);

#endif
