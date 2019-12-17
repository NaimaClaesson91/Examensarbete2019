#include <avr/io.h>
#include <stdio.h>

#include "uart.h"


static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0 | 1 << RXEN0);
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

	stdout = &uart_stdout;
}

void uart_tx_disable(){

	UCSR0B &= ~(1 << TXEN0);
}

void uart_tx_enable(){

	UCSR0B |= (1 << TXEN0);
}

int uart_putchar(char chr, FILE *stream) {

	while (!(UCSR0A & (1 << UDRE0)))
	{

	}
	UDR0 = chr;
	return 0;
}

void uart_print_char(char chr) {
	while (!(UCSR0A & (1 << UDRE0)))
	{

	}
	UDR0 = chr;	
}

char uart_getchar(void) {
	while (!(UCSR0A & (1 << RXC0)))
	{

	}
	return UDR0;
}

void uart_putstr(const char *str){

	while (*str) {

		uart_putchar(*str++, NULL);
	}

}


void uart_print(const char * string){

	while(*string != '\0'){
		uart_print_char(*string);
		string++;
	}

	uart_print_char('\r');
	uart_print_char('\n');
}

void uart_getstring(char * string, uint8_t max_length){

	uint8_t characters = 0;
	while(characters < (max_length - 1)){
		string[characters] = uart_getchar();

		if(string[characters] == '\n'){
			string[++characters] = '\0';
			break;
		}

		characters++;
	}
}