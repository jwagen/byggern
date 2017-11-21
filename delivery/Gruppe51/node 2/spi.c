/*
 * spi.c
 *
 * Created: 29.09.2017 09:42:47
 *  Author: johanwaa
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "spi.h"

void spi_init(void){
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB1)|(1<<PB2);
	
	//Set SS as output
	DDRB |= (1<<PB7);
	
	//Set SS input as output, as it will set spi mode to slave if it is not done
	DDRB |= (1<<PB0);
	
	//Set MISO as input
	DDRB &= ~(1<<PB3);
	
	//Set spi clk to fosc/2
	SPSR |= (1<<SPI2X);
	/* Enable SPI, Master */
	SPCR = (1<<SPE)|(1<<MSTR);
}

uint8_t spi_transmit(uint8_t data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	
	data = SPDR;

	return data;
}