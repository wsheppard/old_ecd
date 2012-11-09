/*
 *
 *
 *
 *    Code for Servo Movement interaction
 *
 */

#include "movement.h"


static float move_sigmoid(float time); /* Find sigmoid position */
static void move_servo_task(void *params); /* Individual servo tasks, one spawned for each servo */
static void move_main_task(void* params); /* Main task manager for this module */
static void move_servo_cont(void); /* Move loop */


/* This is the INCOMING queue */
static xQueueHandle qMove;

typedef struct {
	xQueueHandle qServo;
	int iServoID;
}move_servoData_s;

/* These are the queues going off to the servo tasks */
static move_servoData_s ServoData[SERVO_COUNT];

int move_Start(xQueueHandle qHandle){

	int x;

	/* Sanity */
	if (qHandle == NULL)
		return ECD_ERROR;

	/* Keep copy of the Queue Handle to use */
	qMove = qHandle;

	/* Create all the servo tasks and their queues */
	for (x=0;x<SERVO_COUNT;x++){

		/* Create queue */
		if(msg_newQueue(&ServoData[x].qServo) != ECD_OK)
			return ECD_ERROR;
		
		ServoData[x].iServoID = x;
	
		/* Create task, pass queue handle in */
		if (xTaskCreate( move_servo_task, 
				"SERVOTASK", 
				configMINIMAL_STACK_SIZE, 
				(void*)&ServoData[x], 
				SERVO_PRIORITY, 
				NULL) != pdPASS){
	
			return ECD_ERROR;
		} 
	

	}



	/* Create main task; return -1 on error */
	if (xTaskCreate( move_main_task, 
		"Movement Main Thread", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		MOVE_PRIORITY, 
		NULL) != pdPASS){
	
			return ECD_ERROR;
	} 
	
	return ECD_OK;
}

static void move_main_task(void* params){

	msg_message_s msgMessage;
	int servoID;

	printf("Movement main task created...\n");

	while(1){
		/* So now wait for commands to come through from the Main Manager
		and send them to the relevant servo task to execute */
		msg_recv_block(qMove, &msgMessage);

		switch (msgMessage.messageID){
			case M_MOVE_CONT:
			case M_MOVE_STOP:
				servoID = msgMessage.messageDATA;
				if (servoID >=PWM_COUNT) break;
				msg_send(ServoData[servoID].qServo,msgMessage);
				//printf("Starting movement on servo %d.\n",msgMessage.messageDATA);
				break;
			case M_MOVE_SPEC:
				break;
			default:
				break;
		}
		
	}

} 

static void move_servo_task(void *params){

	move_servoData_s servoData;
	int position = 0;
	msg_message_s msgMessage;

	/* Grab local copy of the queue handle */
	servoData = *(move_servoData_s*)params;

	//printf("I am servo task %d.\n", servoData.iServoID);

	while(1){

		/* Block on queue */
		msg_recv_block(servoData.qServo, &msgMessage);

		/* Is it a Specific Move, or Continous Move command? */
		switch (msgMessage.messageID){
			case M_MOVE_CONT:
				printf("Servo task %d started moving.\n", servoData.iServoID);
				//move_servo_cont();
				break;
			case M_MOVE_SPEC:
				break;
			case M_MOVE_STOP:
				printf("Servo task %d stopped moving.\n", servoData.iServoID);
				//printf("Stopping movement on servo %d.\n",msgMessage.messageDATA);
				break;
			default:
				break;
		}
		//pwm_set_pos(servoData.iServoID, position);
	}
}


static void move_servo_cont(void){
	
	/* Need to know direction and servo number! */

	/* Move one step of continous move */


}

float move_sigmoid(float time){



}