//UART funksjoner for seriell komunikasjon

#ifndef UART_H_
#define UART_H_
#include <stdio.h>



extern FILE uart_str;


void uart_init();
unsigned char uart_receive(FILE *stream);
uint8_t uart_transmit(unsigned char data, FILE *stream);




#endif