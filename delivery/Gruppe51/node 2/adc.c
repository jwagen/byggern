/*
 * adc.c
 *
 * Created: 15.09.2017 10:10:50
 *  Author: mohamama
 */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>


//Initialize internal adc
void adc_init(void){
	//Use avcc as vref
	ADMUX |= (1<<REFS0);

	//Set prescaler to 128
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	//Set ADC auto triger mode
	ADCSRA |= (1<<ADATE);
	
	
	//Turn on adc, start conversion
	ADCSRA |= (1<<ADEN) | (1<<ADSC);
	 
}

//Read adc channel
uint16_t adc_read(uint8_t channel){
	//The channel needs to be set here, but it works as only channel 0 is used.
	return ADC;
}