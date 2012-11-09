#ifndef KEYPAD_H
#define KEYPAD_H

/* Free RTOS includes */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Local Includes */
#include "ECD.h"
#include "messaging.h"

/* How often to POLL (in ticks between polls).*/
#define KP_DELAY 300

/* Task priority */
#define KP_PRIORITY tskIDLE_PRIORITY

/* Called to start off the task; Give the message queue handle to 
	which it should put keypad events onto. if successful it will return ok. */
int kp_startTask(xQueueHandle);

#endif