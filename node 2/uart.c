#include "uart.h"

#define BAUDRATE 9600
#define BAUD_PRESCALE (((( F_CPU / 16) + ( BAUDRATE / 2) ) / ( BAUDRATE )) - 1)
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

FILE uart_str = FDEV_SETUP_STREAM (uart_transmit, uart_receive, _FDEV_SETUP_RW);


void uart_init(){

	// Set baudrate to 9600

	UBRR0H |= (BAUD_PRESCALE >> 8);
	UBRR0L |= BAUD_PRESCALE;
	// Enable TX rx
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	

	
	//uart_str = fdevopen(uart_transmit, uart_receive);
	stdout = stdin = &uart_str;
	
}

void uart_transmit(unsigned char data, FILE* stream){
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	UDR0 = data;
}

//Function to receive data
unsigned char uart_receive(FILE* stream){
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}






