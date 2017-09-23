/*
 * button.h
 *
 * Created: 15.09.2017 12:32:46
 *  Author: mohamama
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


void button_init(void);
uint8_t button_read(uint8_t button);

typedef enum buttons {
	LEFT_BUTTON,
	RIGHT_BUTTON
}buttons_t;


#endif /* BUTTON_H_ */