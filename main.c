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
#include "sram.h"



int main(void)
{
	uart_init();
	sram_init();
	printf("Init done");
	printf("Starting SRAM test");
	sram_test();
	printf("Finished SRAM test");
	while(1){
		
	}
	
}