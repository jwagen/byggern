#include "uart.h"

#include "defines.h"

#define BAUDRATE 9600
#define BAUD_PRESCALE (((( F_CPU / 16) + ( BAUDRATE / 2) ) / ( BAUDRATE )) - 1)
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void uart_init(){

	// Set baudrate to 9600

	UBRR1H |= (BAUD_PRESCALE >> 8);
	UBRR1L |= BAUD_PRESCALE;
	// Enable TX rx
	UCSR1B = (1<<TXEN1)|(1<<RXEN1);	
	
	fdevopen(uart_transmit, uart_receive);
	
}


void uart_transmit(unsigned char data){
	while ( !( UCSR1A & (1<<UDRE1)) );
	
	UDR1 = data;
}

//Function to receive data
unsigned char uart_receive(void){
	while (!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

