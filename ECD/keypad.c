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
#include "pwm.h"

/* Private functions */
static void kp_main(void*pvParams);
static void kp_getCurrent(unsigned short *KP_data);

/* Private Variables */
xQueueHandle qKP;
xTaskHandle tKP;


int kp_startTask(xQueueHandle qHandle){
	
	if (qHandle == NULL)
		return ECD_ERROR;

	/* Keep copy of the Queue Handle to use */
	qKP = qHandle;

	/* Create main task; return -1 on error */
	if (xTaskCreate( kp_main, 
		"KP Main Thread", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		KP_PRIORITY, 
		&tKP) != pdPASS){
	
			return ECD_ERROR;
	} 

	return ECD_OK;

}

static void kp_main(void*pvParams){

	unsigned short kp_previousData = 0;
	unsigned short kp_currentData = 0;
	msg_message_s mMessage;

	/* Get current values */
	//kp_getCurrent(&kp_currentData);

	//kp_previousData = kp_currentData;
	kp_previousData = 0;


	printf("Keypad starting...\n");

	vTaskDelay(1000);

	/* Start checking for keypad changes and then send as message */
	for (;;){
	
		kp_getCurrent(&kp_currentData);

		//printf("Data: Previous[%x], Current:[%x].\n", kp_previousData, kp_currentData);
		
	

		/* If there is a change */
		if (kp_previousData ^ kp_currentData){
			mMessage.messageID = M_KP_EVENT;
			mMessage.messageDATA = (kp_currentData << 16) | ((unsigned short)65535 & (kp_previousData ^ kp_currentData));
			
			msg_send(qKP,mMessage);

			kp_previousData = kp_currentData;
		}

		vTaskDelay(KP_DELAY);
	
	}

}


static void kp_getCurrent(unsigned short *KP_data){
	/* Get the state of all the KeyPad buttons and put into a nice 16bits */

	int x,y;
	static unsigned short output = 3;

	//printf("Checking keypad....\n");

	/* Now loop through all the combinations to find the button states */
	for (x=0;x<4;x++){
	
		/* Set the relevant register to LOW */

		for (y=0;y<4;y++){
		
			/* Check if the particular key is pressed */
		
		}
	
	}


	*KP_data = output;
	output <<= 1;
}

