#ifndef PWM_H
#define PWM_H

#include "ECD.h"

/* Put in the addresses of the servos or the auto-genreated defines */
#define ADD_SERVO1 0x10000000
#define ADD_SERVO2 0x20000000
#define ADD_SERVO3 0x30000000
#define ADD_SERVO4 0x40000000

enum {
	PWM_SERVO1,
	PWM_SERVO2,
	PWM_SERVO3,
	PWM_SERVO4,
	PWM_COUNT,
};

/* TODO: Need to think about the mix and max values for the posiiton - what 
	resolution are we going to use? I've assumed simple percentage but this might be 
	too small */
typedef struct {
	int address;
	int position;
	int defaultposition;
}pwm_servo_data_s;

/* These functions need to be mutex protected so that multiple writes to one servo are prevented */

/* Set position on particular servo */
int pwm_set_pos(int servo, int position);

/* Get the current position on that servo.
	This implies that this module keeps track of the position? */
//int pwm_get_pos(int servo, int* position);

#endif