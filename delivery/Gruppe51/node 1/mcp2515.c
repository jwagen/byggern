/*
 * mcp2515.c
 *
 * Created: 29.09.2017 10:07:31
 *  Author: johanwaa
 */ 

#include <stdint.h>
#include <avr/io.h>

#include "mcp2515.h"
#include "spi.h"


void mcp2515_disable(){
	//Set CS high
	PORTB |= (1<<PB4);
}

void mcp2515_enable(){
	//Set CS low
	PORTB &= ~(1<<PB4);	
}

void mcp2515_init(){
	spi_init();
}

//Read data from register beginning at selected address.
uint8_t mcp2515_read(uint8_t address){
	uint8_t data;
	
	mcp2515_enable();
	spi_transmit(0x03);
	spi_transmit(address);
	
	//recive data
	data = spi_transmit(0);
	mcp2515_disable();	
	return data;
}

//Write data to register beginning at selected address.
void mcp2515_write(uint8_t address, uint8_t data){
	mcp2515_enable();
	spi_transmit(0x02);
	spi_transmit(address);
	
	//send data
	spi_transmit(data);
	mcp2515_disable();
}

//Instructs controller to begin message transmission sequence for
//any of the transmit buffers
void mcp2515_rts(uint8_t registers){
	mcp2515_enable();
	spi_transmit(0x80 | (7 & registers));
	mcp2515_disable();
}

//Quick polling command that reads several status bits for transmit and receive functions
uint8_t mcp2515_read_status(){
	uint8_t data;
	mcp2515_enable();
	spi_transmit(0xa0);
	data = spi_transmit(0);
	mcp2515_disable();
	return data;
}

//Allows the user to set or clear individual bits in a particular
//register. Note: Not all registers can be bit-modified with this
//command.
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	mcp2515_enable();
	spi_transmit(0x05);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	mcp2515_disable();
}

//Resets internal registers to default state,
void mcp2515_reset(){
	mcp2515_enable();
	spi_transmit(0xc0);
	mcp2515_disable();
}