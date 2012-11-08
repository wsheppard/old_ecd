/*
 *
 *
 *
 *    Code for PWM interaction
 *
 */

#include "pwm.h"

/* Fill private data about servos, the position data is kept track of privately
   in this module - so might need some functions to get it out? */
static pwm_servo_data_s servo_data[PWM_COUNT]={
	{ADD_SERVO1,0,50},
	{ADD_SERVO2,0,50},
	{ADD_SERVO3,0,50},
	{ADD_SERVO4,0,50},
};


int pwm_set_pos(int servo, int position){

	return 0;
}



	
	