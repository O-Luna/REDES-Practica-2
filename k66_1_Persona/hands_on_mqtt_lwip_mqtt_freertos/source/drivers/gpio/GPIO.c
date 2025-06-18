/*
 * GPIO.c
 *
 *  Created on: 16 may. 2025
 *      Author: megae
 */

/*
 * botones.c
 *
 *  Created on: 11 mar. 2025
 *      Author: megae
 */

#include "GPIO.h"



bool presion=false;

void PORTA_IRQHandler(void) {
    // Limpiar la bandera de interrupción del pin PTA10 = sw3
    if (PORTA->ISFR & (1 << 10)) {
    	PORTA->ISFR |= (1 << 10); //limpiar bandera
    	presion=!presion;

    }
}
void PORTD_IRQHandler(void) {
    // Limpiar la bandera de interrupción del pin PTA10 = sw3
    if (PORTD->ISFR & (1 << 11)) {
    	PORTD->ISFR |= (1 << 11); //limpiar bandera
    	//sw3--;

    }
}

