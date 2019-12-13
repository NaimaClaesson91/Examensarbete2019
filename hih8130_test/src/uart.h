#ifndef UART_H_
#define UART_H_

#define BAUDRATE 9600
#define UBRR (F_CPU/16/BAUDRATE-1)

void uart_init(void);

void uart_tx_disable(void);
void uart_tx_enable(void);

int uart_putchar(char chr, FILE *stream);

char uart_getchar(void);

void uart_putstr(const char *str);

void uart_print_char(char chr);

void uart_print(const char * string);

void uart_getstring(char * string, uint8_t max_length);
#endif
