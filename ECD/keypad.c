/*
 *
 *
 *
 *    Code for KEYPAD interaction
 *	This should be an endless loop which delivers a message with the 16bit value representing
	the different states of the buttons. This will happen using a queue system.
  */

/* Local includes */
#include "keypad.h"

/* Private functions */
static void KP_main(void*pvParams);
static void KP_getCurrent(unsigned short *KP_data);

/* Private Variables */
xQueueHandle qKP;
xTaskHandle tKP;


int KP_startTask(xQueueHandle qHandle){
	
	if (qHandle == NULL)
		return -1;

	/* Keep copy of the Queue Handle to use */
	qKP = qHandle;

	/* Create main task; return -1 on error */
	if (xTaskCreate( KP_main, 
		"KP Main Thread", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		KP_PRIORITY, 
		&tKP) != pdPASS){
	
			return -1;
	} 

	return 0;

}

static void KP_main(void*pvParams){

	unsigned short KP_previousData = 0;
	unsigned short KP_currentData = 0;
	msg_message_s mMessage;

	/* Get current values */
	KP_getCurrent(&KP_currentData);

	KP_previousData = KP_currentData;

	/* Start checking for keypad changes and then send as message */
	while(1){
	
		KP_getCurrent(&KP_currentData);

		printf("Data is: %d, %d.\n", KP_previousData, KP_currentData);



		/* If there is a change */
		if (KP_previousData ^ KP_currentData){
			mMessage.messageID = M_KPEVENT;
			mMessage.messageDATA = (KP_currentData << 16) | ((unsigned short)65535 & (KP_previousData ^ KP_currentData));
			
			msg_send(qKP,mMessage);

			KP_previousData = KP_currentData;
		}

		vTaskDelay(KP_DELAY);
	
	}

}


static void KP_getCurrent(unsigned short *KP_data){
	/* Get the state of all the KeyPad buttons and put into a nice 16bits */

	static unsigned short test = 45;

	printf("Checking keypad....\n");

	*KP_data ^= test;

}

