/*
 * GccApplication1.c
 *
 * Created: 01.09.2017 09:56:39
 *  Author: mohamama
 */ 

#define F_CPU 4915200


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"



int main(void)
{
	uart_init();

	DDRA |= (1 << PA0);
	PORTA &= !(1 << PA0);

	
	PORTA |= (1 << PA0);
	
	char buffer [20];
	
	printf("Ready\n");

    while(1)
    {
		scanf("%s", buffer);
		printf(buffer);
		printf("\n");
	
		
    }
	
}