#ifndef SERIAL_H_
#define SERIAL_H_

#define BAUDRATE 38400
#define UBRR (16000000/16/BAUDRATE-1)

void uart_init(void);

int uart_putchar(char chr, FILE *stream);

char uart_getchar(void);

void uart_putstr(const char *str);

#endif