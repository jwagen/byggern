/*
 * dac.c
 *
 * Created: 03.11.2017 10:12:03
 *  Author: johanwaa
 */

#include <stdint.h>
#include <stdio.h>
#include "dac.h"
#include "TWI_Master.h"

#define ADC_I2C_ADDRESS_W 0x50 

//Initialize the I2C comunication
void dac_init(){
	TWI_Master_Initialise();
}

//Write a value to the dac, at specified channel
void dac_write(uint8_t channel, uint8_t value){
	uint8_t message [3];
	
	//Set address and read write bit, 
	//Read write bit is zero for write, and is LSB of address.
	message[0] = ADC_I2C_ADDRESS_W;
	
	//Set command byte, RST = 0, PD = 0, A2 = 0, [A1 A0] = channel
	message[1] = 3 & channel;
	
	//Set value of output
	message[2] = value;
	
	//printf("Address = %d, command = %d, value = %d\n", message[0], message[1], message[2]);
	
	//Transmit data over I2C
	TWI_Start_Transceiver_With_Data(message , 3);

	
}