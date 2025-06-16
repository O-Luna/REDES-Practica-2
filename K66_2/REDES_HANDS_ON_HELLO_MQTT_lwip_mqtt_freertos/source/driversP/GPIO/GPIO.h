/*
 * GPIO.h
 *
 *  Created on: 17 may. 2025
 *      Author: megae
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#define PUBLISH_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary initialization thread. */
#define PUBLISH_THREAD_PRIO DEFAULT_THREAD_PRIO

void button_driver_init(void);


typedef struct {
	const char *topic;
	const char *message;
} mqtt_args_t;

