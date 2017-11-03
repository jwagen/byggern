/*
 * dac.h
 *
 * Created: 03.11.2017 10:12:17
 *  Author: johanwaa
 */ 


#ifndef DAC_H_
#define DAC_H_

#include <stdint.h>


void dac_init();

void dac_write(uint8_t channel, uint8_t value);





#endif /* DAC_H_ */