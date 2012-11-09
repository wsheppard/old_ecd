#include "messaging.h"

int msg_newQueue(xQueueHandle*qhandle){
	
	xQueueHandle tempHandle = NULL;
	tempHandle = xQueueCreate(MSG_QUEUE_LENGTH, sizeof(msg_message_s));

	/* Sanity */
	if (qhandle == NULL){
		return ECD_ERROR;
	}

	if (tempHandle == 0) {
		/* Return error as couldn't create queue */
		return ECD_ERROR;
	}
	else {
		/* Set handle and return OK */
		*qhandle = tempHandle;
		return ECD_OK;
	}

	return ECD_ERROR;

}

int msg_rmQueue(xQueueHandle qHandle){
	
	if (qHandle == 0)
		return -1;

	vQueueDelete(qHandle);
	
	return ECD_OK;
}


int msg_send(xQueueHandle qHandle, msg_message_s msgMessage){

	/* Send it to the back of the queue, don't wait for the queue 
		if it's full */
	if (xQueueSendToBack(qHandle, (void*)&msgMessage, 0) != pdTRUE){
		printf("Sent message failed...\n");
		return -1;
	}
	else{
		//printf("Sent message...\n");
		return 0;
	}

}



int msg_recv_noblock(xQueueHandle qHandle, msg_message_s*pMessage){

	if (qHandle == NULL){
		return ECD_ERROR;
	}

	if(pdTRUE==xQueueReceive( qHandle, pMessage, 0 )){
		return ECD_OK;
	}
	else{
		return ECD_NOMSG;
	}


}

int msg_recv_block(xQueueHandle qHandle, msg_message_s*pMessage){

	if (qHandle == NULL){
		return ECD_ERROR;
	}

	xQueueReceive( qHandle, pMessage, portMAX_DELAY );
	
	return ECD_OK;

}