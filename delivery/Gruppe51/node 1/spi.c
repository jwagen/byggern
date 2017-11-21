/*
 * spi.c
 *
 * Created: 29.09.2017 09:42:47
 *  Author: johanwaa
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "spi.h"

//Set up registers for spi transfer
void spi_init(void){
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB4)|(1<<PB5)|(1<<PB7);
	
	//Set MISO as input
	DDRB &= ~(1<<PB6);
	
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


//Transmit and recive a single byte. This happens simunatinusly in SPI.
uint8_t spi_transmit(uint8_t data){
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	
	data = SPDR;

	return data;
}