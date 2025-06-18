/*
 * uart_d.h
 *
 *  Created on: 18 jun. 2025
 *      Author: oralu
 */

#ifndef DRIVERSP_UART_UART_D_H_
#define DRIVERSP_UART_UART_D_H_

#include "driversP/mqtt/mqtt.h"
#include "driversP/GPIO/GPIO.h"
#include "driversP/UART/uart_d_cfg.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include <stdbool.h>
#include <stdio.h>

#define DEBUG_UART UART0
#define DEBUG_UART_CLKSRC kCLOCK_CoreSysClk

void uart_init(void);

#endif /* DRIVERSP_UART_UART_D_H_ */
