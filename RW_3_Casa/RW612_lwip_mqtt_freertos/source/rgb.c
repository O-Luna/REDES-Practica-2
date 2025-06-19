/*
 * rgb.c
 *
 *  Created on: 19 jun. 2025
 *      Author: armzr
 */
#include "rgb.h"

void init_RGB(void)
{
	gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput,
	    0,
	};

	GPIO_PinInit(GPIO, 0U, 0U, &led_config); // Azul
	GPIO_PinWrite(GPIO, 0U, 0U, 1);

	GPIO_PinInit(GPIO, 0U, 1U, &led_config); // Rojo
	GPIO_PinWrite(GPIO, 0U, 1U, 1);

	GPIO_PinInit(GPIO, 0U, 12U, &led_config); // Verde
	GPIO_PinWrite(GPIO, 0U, 12U, 1);

	GPIO_PortToggle(GPIO, 0U, 1u << 12U);
}
