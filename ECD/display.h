#ifndef DISPLAY_H
#define DISPLAY_H

/* Free RTOS includes */
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Local Includes */
#include "ECD.h"
#include "messaging.h"

#define DISPLAY_PRIORITY tskIDLE_PRIORITY

int display_init(void);

#endif