/*
 *
 *  Will's first attempt at writing FreeRTOS code....
 */

/* Standard includes. */
#include <stdio.h>

/* Kernel includes. */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#include "messaging.h"
#include "keypad.h"


#define mainTIMER_TEST_PERIOD			( 50 )

/* The variable into which error messages are latched. */
static char *pcStatusMessage = "OK";

/* This semaphore is created purely to test using the vSemaphoreDelete() and
semaphore tracing API functions.  It has no other purpose. */
static xSemaphoreHandle xMutexToDelete = NULL;

static void task1(void* bla);

/*-----------------------------------------------------------*/



static void task1(void* bla){
	
	while(1){
		printf("Hello\n");
		vTaskDelay(100);
	}


}


int main( void )
{
	xQueueHandle qKP; /* Queue handle for the KEYPAD */

	printf("Starting the RTOS demo.....\n");

	xTaskCreate( task1, "Hello", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

	/* Create queue for keypad */
	msg_newQueue(&qKP);

	/* Start keypad task and give it the queue handle */
	KP_startTask(qKP);
	
	/* Start the scheduler itself. */
	vTaskStartScheduler();

    /* Should never get here unless there was not enough heap space to create 
	the idle and other system tasks. */
    return 0;
}
/*-----------------------------------------------------------*/

void vAssertCalled( void )
{
	taskDISABLE_INTERRUPTS();
	for( ;; );
}

