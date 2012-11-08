/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "messages.h"

/* Data type for sending message */
typedef struct {
	int messageID;
	int messageDATA;
}msg_message_s;

typedef xQueueHandle msg_handle;

#define MSG_QUEUE_LENGTH 10

/* Get handle to a new queue */
int msg_newQueue(xQueueHandle*);

/* Close queue */
int msg_rmQueue(xQueueHandle);

/* Push new message onto end of queue */
int msg_send(xQueueHandle, msg_message_s);

/* Wait for message indefinately */
int msg_recv(xQueueHandle, msg_message_s*);