/*
 *
 *
 *
 *    Code for Servo Movement interaction
 *
 */

#include "movement.h"

/* This is the INCOMING queue */
static xQueueHandle qMove;

static xSemaphoreHandle xSemaphore = NULL;

/* Position info is kept in the servo task */
typedef struct {
	xQueueHandle qServo;
	int iServoID;
	unsigned position;
	int state;
}move_servoData_s;

static float move_sigmoid(float time); /* Find sigmoid position */
static void move_servo_task(void *params); /* Individual servo tasks, one spawned for each servo */
static void move_main_task(void* params); /* Main task manager for this module */
static void move_servo_cont(move_servoData_s *sData, int direction); /* Move loop */

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

	xSemaphore = xSemaphoreCreateMutex();

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

	for(;;){
		/* So now wait for commands to come through from the Main Manager
		and send them to the relevant servo task to execute */
		msg_recv_block(qMove, &msgMessage);

		switch (msgMessage.messageID){
			case M_MOVE_CONT:
			case M_MOVE_STOP:
				/* Mask off 8bit servo number */
				servoID = M_MOVE_SERVOMASK & msgMessage.messageDATA;
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
	msg_message_s msgMessage;

	/* Grab local copy of the queue handle */
	servoData = *(move_servoData_s*)params;

	//printf("I am servo task %d.\n", servoData.iServoID);

	for(;;){

		/* Block on queue */
		msg_recv_block(servoData.qServo, &msgMessage);

		/* Is it a Specific Move, or Continous Move command? */
		switch (msgMessage.messageID){
			case M_MOVE_CONT:
				move_servo_cont(&servoData,(msgMessage.messageDATA & M_MOVE_DIRMASK));
				ServoData[servoData.iServoID].state = MOVE_STATE_STOP;
				break;
			case M_MOVE_SPEC:
				break;
			case M_MOVE_STOP:
				/* Shouldn't really be valid here */
				printf("Servo task %d stopped moving.\n", servoData.iServoID);
				//printf("Stopping movement on servo %d.\n",msgMessage.messageDATA);
				break;
			default:
				break;
		}
		
	}
}


void move_servo_cont(move_servoData_s *sData, int direction){
	
	msg_message_s msgMessage;

	if (direction & M_MOVE_DIRMASK) 
		ServoData[sData->iServoID].state = MOVE_STATE_INC;
	else
		ServoData[sData->iServoID].state = MOVE_STATE_DEC;

	for(;;){

		/* Quick message check */
		if(msg_recv_noblock(sData->qServo, &msgMessage)!=ECD_NOMSG){
			if(msgMessage.messageID!=M_MOVE_STOP){
				printf("Expecting STOP message but received something else!\n");
				return;
			}
			else{
				//printf("Servo task %d STOPPING %s.\n", sData->iServoID,direction ? "INC": "DEC");
				return;
			}
		}
	
		/* So no message received, move one step */
		//printf("Servo task %d moving %s STEP.\n", sData->iServoID,direction ? "INC": "DEC");
	
		if (direction & M_MOVE_DIRMASK)
			pwm_jump(sData->iServoID, MOVE_JUMPVAL);
		else
			pwm_jump(sData->iServoID, -MOVE_JUMPVAL);

		vTaskDelay(MOVE_LATENCY);
	
	
	}

}

int move_get_state(int servo, int*state){

	/* This might need mutex protection if it become an important thing, atm its
		just used in displaying so not really worth it. */
	*state = ServoData[servo].state;
		
	return ECD_OK;
}
