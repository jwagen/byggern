/*
 * motor.h
 *
 * Created: 03.11.2017 11:15:41
 *  Author: johanwaa
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>




extern volatile int16_t motor_pid_setpoint;
extern volatile int16_t motor_pid_curr_pos;
extern volatile int16_t motor_pid_errorsum;
extern volatile int16_t motor_pid_error;
extern volatile int16_t motor_pid_output;

void motor_init();

void motor_enable(uint8_t enable);

void motor_set_speed(uint8_t);
void motor_set_direction(uint8_t);

int16_t motor_get_encoder(void);

void motor_set_pos(int8_t);




#endif /* MOTOR_H_ */