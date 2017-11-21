/*
 * mcp2515.h
 *
 * Created: 29.09.2017 10:07:14
 *  Author: johanwaa
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_

#include <stdint.h>


typedef enum {
	TXB0 = 1,
	TXB1 = 2,
	TXB2 = 4
}mcp2515_tx_buffers;


void mcp2515_init();
uint8_t mcp2515_read(uint8_t address);
void mcp2515_write(uint8_t address, uint8_t data);


void mcp2515_rts(uint8_t registers);
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp2515_reset();



#endif /* MCP2515_H_ */