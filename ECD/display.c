/*
 *
 *
 *   Display Modules
 *   Looks after displaying info to the user.
 *
 *
 */

#include "display.h"

#include <stdio.h>
#include "pwm.h"
#include "movement.h"

static void display_main(void*params);




int display_init(void){
	
	/* Create main task; return -1 on error */
	if (xTaskCreate( display_main, 
		"Display Thread", 
		configMINIMAL_STACK_SIZE, 
		NULL, 
		DISPLAY_PRIORITY, 
		NULL) != pdPASS){
	
			return ECD_ERROR;
	} 
	return ECD_OK;
}


void display_main(void*params){

	unsigned int pos[4];
	int state[4];
	int x;

	for(;;){
	
		for(x=0;x<PWM_COUNT;x++){ 
			pwm_get_pos(x,&pos[x]);
			move_get_state(x,&state[x]);
		}

		printf("Servos P:S [%u:%u],[%u:%u],[%u:%u],[%u:%u].\n",
			pos[0],state[0],
			pos[1],state[1],
			pos[2],state[2],
			pos[3],state[3]);
	
		vTaskDelay(50);
	
	}




}

