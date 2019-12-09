#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include "serial.h"


int main(void)
{
    
    while (1) 
    {
		printf("Hej\n");
		_delay_ms(2000);
    }
}

