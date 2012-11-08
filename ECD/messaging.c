#include "messaging.h"

//static xQueueHandle msg_queues[MSG_MAX_QUEUES] = {NULL,};
//static int msg_queueCount = 0;

int msg_newQueue(xQueueHandle*qhandle){
	
	xQueueHandle tempHandle = NULL;
	tempHandle = xQueueCreate(MSG_QUEUE_LENGTH, sizeof(msg_message_s));

	/* Sanity */
	if (qhandle == NULL){
		return -1;
	}

	if (tempHandle == 0) {
		/* Return error as couldn't create queue */
		return -1;
	}
	else {
		/* Set handle and return OK */
		*qhandle = tempHandle;
		return 0;
	}

	return -1;

}

int msg_rmQueue(xQueueHandle qHandle){
	
	if (qHandle == 0)
		return -1;

	vQueueDelete(qHandle);
	
	return 0;
}


int msg_send(xQueueHandle qHandle, msg_message_s msgMessage){

	/* Send it to the back of the queue, don't wait for the queue 
		if it's full */
	if (xQueueSendToBack(qHandle, (void*)&msgMessage, 0) != pdTRUE){
		return -1;
	}
	else{
		return 0;
	}

}


int msg_recv(xQueueHandle qHandle, msg_message_s*pMessage){

	if (qHandle == NULL){
		return -1;
	}

	xQueueReceive( qHandle, pMessage, ( portTickType ) 10 );
	
	return 0;

}