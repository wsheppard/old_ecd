#ifndef PWM_H
#define PWM_H

#include "ECD.h"
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

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
	const int address;
	int position;
	int defaultposition;
}pwm_servo_data_s;

/* These functions need to be mutex protected so that multiple writes to one servo are prevented */

int pwm_init(void);

/* Set position on particular servo - directly into the PWM hardware module. */
int pwm_set_pos(int servo, unsigned int position);

/* Budge the arm from where it already is. Negative and positive 
	imply direction of the jump parameter */
int pwm_jump(int servo, int jump);

/* Get the current position on that servo from the PWM HARDWARE
	*/
int pwm_get_pos(int servo, unsigned int* position);

#endif