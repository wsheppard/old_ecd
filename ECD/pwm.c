/*
 *
 *
 *
 *    Code for PWM interaction
 *
 */

/* Put in the addresses of the servos or the auto-genreated defines */
#define ADD_SERVO1 0x10000000
#define ADD_SERVO2 0x20000000
#define ADD_SERVO3 0x30000000
#define ADD_SERVO4 0x40000000

typedef enum _servo_en{
	PWM_SERVO1,
	PWM_SERVO2,
	PWM_SERVO3,
	PWM_SERVO4,
	PWM_COUNT,
}servo_en;

typedef struct _servo_data_s{
	int address;
	int position;
}servo_data_s;

/* Fill private data about servos */
static servo_data_s servo_data[PWM_COUNT]={
	{ADD_SERVO1,0},
	{ADD_SERVO2,0},
	{ADD_SERVO3,0},
	{ADD_SERVO4,0},
};

/* Set position on particular servo */
int PWM_set_pos(servo_en servo, int position);

/* Get the current position on that servo.
	This implies that this module keeps track of the position? */
int PWM_get_pos(servo_en servo, int* position);
