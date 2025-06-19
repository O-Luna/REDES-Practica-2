
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "driversP/UART/uart_d.h"
#include "driversP/mqtt/mqtt.h"

#define PUBLISH_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary initialization thread. */
#define PUBLISH_THREAD_PRIO DEFAULT_THREAD_PRIO

void button_driver_init();
void leds_init();

void red_led_toggle();
void green_led_toggle();
void blue_led_toggle();
void data_received(char dato[]);

extern SemaphoreHandle_t xRedLedSemaphore;
extern SemaphoreHandle_t xGreenLedSemaphore;
extern SemaphoreHandle_t xBlueLedSemaphore;
