/*
 *
 *
 *
 *    Code for PWM interaction

*	This should be an endless loop which delivers a message with the 16bit value representing
	the different states of the buttons. This will happen using a queue system.
  */

#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Called to start off the task; if successful it will return ok. */
int KP_startTask(void);

//int KP_check(int* 


int KP_startTask(void){
	


}