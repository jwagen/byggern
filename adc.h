/*
 * adc.h
 *
 * Created: 15.09.2017 10:10:36
 *  Author: mohamama
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void adc_init(void);

uint8_t adc_read(uint8_t channel);




#endif /* ADC_H_ */