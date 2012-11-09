#ifndef MOVEMENT_H
#define MOVEMENT_H

/* Must define the global latency for writing to PWM in ticks. This is the
   time inbetween successive writes to the PWM module. 
   */
#include "pwm.h"
#include "messaging.h"
#include "ECD.h"

/* Config */
#define MOVE_LATENCY 100
#define SERVO_COUNT PWM_COUNT
#define MOVE_JUMPVAL 2

/* Task priority */
#define MOVE_PRIORITY tskIDLE_PRIORITY 
#define SERVO_PRIORITY tskIDLE_PRIORITY

enum {
	MOVE_STATE_STOP,
	MOVE_STATE_INC,
	MOVE_STATE_DEC,
	MOVE_STATE_COUNT
};


/* Set up the module, give it the queue to receive messages from */ 
int move_Start(xQueueHandle);

int move_get_state(int servo, int* state);

#endif