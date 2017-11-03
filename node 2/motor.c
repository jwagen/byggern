/*
 * motor.c
 *
 * Created: 03.11.2017 11:15:56
 *  Author: johanwaa
 */
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>

#include "motor.h"
#include "dac.h"


#define MOTOR_CONTROLL_PORT PORTH
#define MOTOR_CONTROLL_DDR  DDRH

#define MOTOR_ENCODER_DDR DDRK
#define MOTOR_ENCODER_PIN PINK


#define MOTOR_EN_PIN  PH4
#define MOTOR_RST_PIN PH6
#define MOTOR_OE_PIN  PH5
#define MOTOR_SEL_PIN PH3
#define MOTOR_DIR_PIN PH1



volatile uint16_t motor_pid_kp = 10;
volatile uint16_t motor_pid_ki = 5;

volatile int16_t motor_pid_setpoint = 0;
volatile int16_t motor_pid_curr_pos = 0;
volatile int16_t motor_pid_errorsum = 0;
volatile int16_t motor_pid_error = 0;



volatile int16_t motor_pid_output = 0;

ISR(TIMER1_OVF_vect){
	motor_pid_curr_pos += motor_get_encoder();
	motor_pid_error = motor_pid_setpoint - motor_pid_curr_pos;
	
	motor_pid_errorsum += motor_pid_error;
	
	motor_pid_output = (motor_pid_kp * motor_pid_error) + (motor_pid_ki * motor_pid_errorsum);
	
	motor_pid_output = motor_pid_output / 32;
	
	if(motor_pid_output < 0){
 		motor_set_direction(0);
		motor_set_speed((uint8_t)(-motor_pid_output));
		
	}
	
	else {
		motor_set_direction(1);
		motor_set_speed((uint8_t)motor_pid_output);
	}

		
}

void motor_init(){
	//Set EN and DIR as outputs
	MOTOR_CONTROLL_DDR |= (1<<MOTOR_EN_PIN) | (1<<MOTOR_DIR_PIN) | (1<<MOTOR_OE_PIN) | (1<<MOTOR_SEL_PIN) | (1<<MOTOR_RST_PIN);
	
	//Set encoder port as input
	MOTOR_ENCODER_DDR = 0;
	
	//Set active low outputs high
	MOTOR_CONTROLL_PORT |= (1<<MOTOR_OE_PIN);
	
	//Set active high outputs low
	MOTOR_CONTROLL_PORT &= ~((1<<MOTOR_EN_PIN) | (1<<MOTOR_DIR_PIN) | (1<<MOTOR_RST_PIN));
	
	dac_init();
	
	//Use timer 1, same as for servo. It runs at 50 Hz. Enable interupt on timer TOP
	TIMSK1 |= (1<<TOIE1);


}

void motor_enable(uint8_t enable){
		if(enable){
			MOTOR_CONTROLL_PORT |= (1<<MOTOR_EN_PIN);
		}
		
		else {
			MOTOR_CONTROLL_PORT &= ~(1<<MOTOR_EN_PIN);
		}
}

void motor_set_speed(uint8_t speed){
	dac_write(0, speed);
}

void motor_set_direction(uint8_t direction){
	if(direction != 0){
		MOTOR_CONTROLL_PORT |= (1<<MOTOR_DIR_PIN);
	}
	
	else {
		MOTOR_CONTROLL_PORT &= ~(1<<MOTOR_DIR_PIN);
	}
}



int16_t motor_get_encoder(void){
	int16_t encoder = 0;
	//Enable output form motor box
	MOTOR_CONTROLL_PORT &= ~(1<<MOTOR_OE_PIN);
	
	
	//Read upper 8 bits
	MOTOR_CONTROLL_PORT &= ~(1<<MOTOR_SEL_PIN);
	_delay_us(20);
	encoder = 0xFF00 & (MOTOR_ENCODER_PIN << 8);
	
	
	
	//Read lower 8 bits
	MOTOR_CONTROLL_PORT |= (1<<MOTOR_SEL_PIN);
	_delay_us(20);
	encoder |= 0x00FF & MOTOR_ENCODER_PIN;
	
	//Reset encoder
	MOTOR_CONTROLL_PORT &= ~(1<<MOTOR_RST_PIN);
	_delay_us(20);
	MOTOR_CONTROLL_PORT |= (1<<MOTOR_RST_PIN);
	
	
	//Disable output from motor box
	MOTOR_CONTROLL_PORT |= (1<<MOTOR_OE_PIN);
	
	return encoder;
	
}

void motor_set_pos(int8_t pos){
	motor_pid_setpoint = pos;
}