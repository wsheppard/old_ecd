/* 

The messaging wrapper for FreeRTOS.

Must have INCLUDE_vTaskSuspend enabled to go for Blocking waits.

*/


#ifndef MESSAGING_H
#define MESSAGING_H

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Local Includes */
#include "messages.h"
#include "ECD.h"

#ifndef INCLUDE_vTaskSuspend
#error Must include ability to suspend tasks.
#endif

/* Data type for sending message */
typedef struct msg_message_ss{
	unsigned int messageID;
	unsigned int messageDATA;
}msg_message_s;

typedef xQueueHandle msg_handle;

#define MSG_QUEUE_LENGTH 10

/* Get handle to a new queue */
int msg_newQueue(xQueueHandle*);

/* Close queue */
int msg_rmQueue(xQueueHandle);

/* Push new message onto end of queue - WILL NOT wait for queue so if it's
	full, we'll get a failed back. */
int msg_send(xQueueHandle, msg_message_s);

/* Check for message, NO wait */
int msg_recv_noblock(xQueueHandle qHandle, msg_message_s*pMessage);

/* Wait for message indefinately */
int msg_recv_block(xQueueHandle qHandle, msg_message_s*pMessage);

#endif