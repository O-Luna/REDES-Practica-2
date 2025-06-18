#include "driversP/mqtt/mqtt.h"
#include "driversP/GPIO/GPIO.h"

static SemaphoreHandle_t xButtonSemaphore = NULL;
static SemaphoreHandle_t xButtonSemaphore2 = NULL;
static void button_task_sw3(void *arg);
static void button_task_sw2(void *arg);


void button_driver_init(void)
{
	// Semáforo binario
	xButtonSemaphore = xSemaphoreCreateBinary();
	xButtonSemaphore2 = xSemaphoreCreateBinary();
	// Task que espera el semáforo
	xTaskCreate(button_task_sw3, "ButtonTask", 256, NULL, 2, NULL);
	xTaskCreate(button_task_sw2, "ButtonTask2", 256, NULL, 2, NULL);
	//Prioridad
	NVIC_SetPriority(PORTA_IRQn, 5);
	NVIC_SetPriority(PORTD_IRQn, 5);
}


static void button_task_sw3(void *arg)
{
	for (;;) {
		if (xSemaphoreTake(xButtonSemaphore, portMAX_DELAY) == pdTRUE) {
			mqtt_args_t *params = pvPortMalloc(sizeof(mqtt_args_t));
			params->topic = "hoa/cuarto/prueba";
			params->message = "ayuda";

			sys_thread_new("publish", pre_publish, (void *)params, 512, 3);
		}
	}
}

static void button_task_sw2(void *arg)
{
	for (;;) {
		if (xSemaphoreTake(xButtonSemaphore2, portMAX_DELAY) == pdTRUE) {
			mqtt_args_t *params = pvPortMalloc(sizeof(mqtt_args_t));
			params->topic = "hoa/cuarto/prueba";
			params->message = "comunicar";

			sys_thread_new("publish", pre_publish, (void *)params, 512, 3);
		}
	}
}



void PORTA_IRQHandler(void) {
    // Limpiar la bandera de interrupción del pin PTA10 = sw3
    if (PORTA->ISFR & (1 << 10)) {
    	PORTA->ISFR |= (1 << 10); //limpiar bandera

    	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    	xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
    	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void PORTD_IRQHandler(void) {
    // Limpiar la bandera de interrupción del pin PTD11 = sw2
    if (PORTD->ISFR & (1 << 11)) {
    	PORTD->ISFR |= (1 << 11); //limpiar bandera

    	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    	xSemaphoreGiveFromISR(xButtonSemaphore2, &xHigherPriorityTaskWoken);
    	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
