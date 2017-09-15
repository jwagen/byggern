/*
 * slider.h
 *
 * Created: 15.09.2017 13:52:55
 *  Author: mohamama
 */ 


#ifndef SLIDER_H_
#define SLIDER_H_
#include <stdint.h>

typedef enum  {
	LEFT_SLIDER,
	RIGHT_SLIDER
}slider_t;


void slider_init(void);
uint8_t slider_read(slider_t slider);





#endif /* SLIDER_H_ */