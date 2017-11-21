/*
 * spi.h
 *
 * Created: 29.09.2017 09:42:59
 *  Author: johanwaa
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

void spi_init(void);

uint8_t spi_transmit(uint8_t data);





#endif /* SPI_H_ */