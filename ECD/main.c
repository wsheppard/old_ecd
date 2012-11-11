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

#include "manager.h"
#include "ECD.h"

#define mainTIMER_TEST_PERIOD			( 50 )

/*-----------------------------------------------------------*/

int main( void )
{

	printf("Starting the RTOS demo.....\n");
	
	/* Starting off the manager thread */
	if (man_start()!=ECD_OK){
	
		printf("Cannot start, halting system!\n");

		for(;;){
		
			Sleep(1000);
		}
	
	}
		
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

