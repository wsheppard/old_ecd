/*
 *
 *
 *
 *    Code for PWM interaction
 *
 */

#include "pwm.h"
#include "semphr.h"
#include <stdio.h>

/* Fill private data about servos, the position data is kept track of privately
   in this module - so might need some functions to get it out? */
pwm_servo_data_s servo_data[PWM_COUNT]={
	{ADD_SERVO1,0,50},
	{ADD_SERVO2,0,50},
	{ADD_SERVO3,0,50},
	{ADD_SERVO4,0,50},
};

static xSemaphoreHandle xSemaphore = NULL;

int pwm_init(void){
	
	int x;

	xSemaphore = xSemaphoreCreateMutex();

	for (x=0;x<PWM_COUNT;x++){
		pwm_set_pos(x,servo_data[x].defaultposition);
	}

	return ECD_OK;
}

int pwm_jump(int servo, int jump){
	
	unsigned int position;

	/* Get current servo position */
	pwm_get_pos(servo, &position);

	if ( (jump<0)&&((-jump)>(int)position)){
		/* Add "jump" to it */
		jump=(-(int)position);
	}

	position += jump;

	/* Write out new servo position */
	pwm_set_pos(servo, position);

	return ECD_OK;
}

int pwm_set_pos(int servo, unsigned int position){

	/* Set this incoming number in hardware for the indicated servo */
	
	//IOWR_32DIRECT(BASE,OFFSET,VALUE);

	 if( xSemaphore != NULL )
    {
        // See if we can obtain the semaphore.  If the semaphore is not available
        // wait 10 ticks to see if it becomes free.	
        if( xSemaphoreTake( xSemaphore, ( portTickType ) 10 ) == pdTRUE )
        {
            // We were able to obtain the semaphore and can now access the
            // shared resource.

            // ...

			servo_data[servo].position = position;

            // We have finished accessing the shared resource.  Release the 
            // semaphore.
            xSemaphoreGive( xSemaphore );
        }
        else
        {
			printf("Couldn't get semaphore...\n");
            // We could not obtain the semaphore and can therefore not access
            // the shared resource safely.
        }
    }

	return ECD_OK;
}

int pwm_get_pos(int servo, unsigned int* position){

	//IORD_32DIRECT(BASE,OFFSET);

		 if( xSemaphore != NULL )
    {
        // See if we can obtain the semaphore.  If the semaphore is not available
        // wait 10 ticks to see if it becomes free.	
        if( xSemaphoreTake( xSemaphore, ( portTickType ) 10 ) == pdTRUE )
        {
            // We were able to obtain the semaphore and can now access the
            // shared resource.

            // ...

			*position = servo_data[servo].position;

            // We have finished accessing the shared resource.  Release the 
            // semaphore.
            xSemaphoreGive( xSemaphore );
        }
        else
        {
			printf("Couldn't get semaphore...\n");
            // We could not obtain the semaphore and can therefore not access
            // the shared resource safely.
        }
    }


	return ECD_OK;
}	