#include "uart.h"

//Interrupt based uart
//The transmit is based on a buffer on interrupt, the recive is not
//NOTE: with this uart driver printf can not be called inside a interrupt.
//It is however much faster for normal use, as it does not block execution of code, waiting to print

#define BAUDRATE 9600
#define BAUD_PRESCALE (((( F_CPU / 16) + ( BAUDRATE / 2) ) / ( BAUDRATE )) - 1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>

//Let printf use uart
FILE uart_str = FDEV_SETUP_STREAM (uart_transmit, uart_receive, _FDEV_SETUP_RW);

//Size of transmit buffer
#define UART_TX_BUFFER_SIZE 64
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE -1)
volatile static char BUFFER[UART_TX_BUFFER_SIZE] = {'a'};
volatile static uint8_t buffer_tail = 0;
volatile static uint8_t buffer_head = 0;

//Runs when transmit buffer is empty
ISR(USART0_UDRE_vect){

	
	//When head and tail are equal the buffer is empty
	if(buffer_head != buffer_tail){

		UDR0 = BUFFER[buffer_tail];

		buffer_tail = ((buffer_tail +1) & UART_TX_BUFFER_MASK);
	}
	
	else {
		//disable interrupt when buffer is empty
		UCSR0B &= ~(1<<UDRIE0);
	}
	
}

//Initialise uart port
void uart_init(){

	// Set baudrate to 9600

	UBRR0H |= (BAUD_PRESCALE >> 8);
	UBRR0L |= BAUD_PRESCALE;
	// Enable TX rx, interupt on empty transmit register
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	

	
	//Set printf and scanf to use the uart
	stdout = stdin = &uart_str;
	
}

//Sends a single character, by adding it to the transmit buffer
uint8_t uart_transmit(unsigned char data, FILE* stream){
	//Wait for interupt transmit to make space in the buffer
	while (buffer_tail == ((buffer_head + 1) & UART_TX_BUFFER_MASK)){
	}
	

	//Write data to head of buffer
	BUFFER[buffer_head] = data;
	buffer_head = (buffer_head +1) & UART_TX_BUFFER_MASK;
	
	//Enable interrupt on empty uart buffer
	UCSR0B |= (1<<UDRIE0);

	return 0;
}

//Function to receive data
//Simple blocking recive
unsigned char uart_receive(FILE* stream){
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}






