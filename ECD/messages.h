/* All the different messages and what they mean */


/* For the KEYPAD module */
#define M_KP_EVENT 1 /* A keypad change of state has occurred */

/* Keys for the KEYPAD module */
#define M_KP_KEY_A1 (1 << 0)
#define M_KP_KEY_A2 (1 << 1)
#define M_KP_KEY_A3	(1 << 2)
#define M_KP_KEY_A4	(1 << 3)
#define M_KP_KEY_B1	(1 << 4)
#define M_KP_KEY_B2	(1 << 5)
#define M_KP_KEY_B3	(1 << 6)
#define M_KP_KEY_B4	(1 << 7)
#define M_KP_KEY_C1	(1 << 8)
#define M_KP_KEY_C2	(1 << 9)
#define M_KP_KEY_C3	(1 << 10)
#define M_KP_KEY_C4	(1 << 11)
#define M_KP_KEY_D1	(1 << 12)
#define M_KP_KEY_D2	(1 << 13)
#define M_KP_KEY_D3	(1 << 14)
#define M_KP_KEY_D4	(1 << 15)

/* Movement module */
#define M_MOVE_CONT 2 /* Start continous movement */
#define M_MOVE_SPEC 3 /* Move 'gracefully' to a specific place */
#define M_MOVE_STOP 4 /* STOP moving */
#define M_MOVE_PLAYBACK 5 /* Start the playback function */
#define M_MOVE_SAVE 6 /* Save current position */
#define M_MOVE_RESET 7 /* delete all saved positions */
#define M_MOVE_RMLAST 8 /* Remove last saved position */

/* For the MOVE CONT message, the DATA is as follows:
	* the lsBYTE is the servo number
	* the 8th but is the direction
	*/
#define M_MOVE_SERVO1 0
#define M_MOVE_SERVO2 1
#define M_MOVE_SERVO3 2
#define M_MOVE_SERVO4 3
#define M_MOVE_SERVOMASK 255
#define M_MOVE_DIRMASK 256
