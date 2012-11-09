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

/* Task priority */
#define MOVE_PRIORITY tskIDLE_PRIORITY 
#define SERVO_PRIORITY tskIDLE_PRIORITY

/* Set up the module, give it the queue to receive messages from */ 
int move_Start(xQueueHandle);


#endif