/*
 * adc.c
 *
 * Created: 15.09.2017 10:10:50
 *  Author: mohamama
 */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

// First address in adc address space
static volatile char *ADC_start_adress = (char *) 0x1400;

//Data for mux config for channel 1 and 2
const uint8_t ADC_mux_channel1 = 0x4;
const uint8_t ADC_mux_channel2 = 0x5;
const uint8_t ADC_mux_channel3 = 0x6;
const uint8_t ADC_mux_channel4 = 0x7;

void adc_init(void){

}

uint8_t adc_read(uint8_t channel){
	uint8_t result = 0;
	
	if(channel == 1){
		*ADC_start_adress = ADC_mux_channel1;
		while((PIND & (1 <<PIND2))){
		}
		
		
		result = *ADC_start_adress;	
	}
	
	else if(channel == 2){
		*ADC_start_adress = ADC_mux_channel2;
		while((PIND & (1 <<PIND2))){
		}
		
		result = *ADC_start_adress;
	}
	
	if(channel == 3){
		*ADC_start_adress = ADC_mux_channel3;
		while((PIND & (1 <<PIND2))){
		}
		
		
		result = *ADC_start_adress;
	}
	
	else if(channel == 4){
		*ADC_start_adress = ADC_mux_channel4;
		while((PIND & (1 <<PIND2))){
		}
		
		result = *ADC_start_adress;
	}	
	
	return result;
}