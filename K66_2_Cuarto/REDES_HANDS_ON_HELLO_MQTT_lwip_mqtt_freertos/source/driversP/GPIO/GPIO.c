#include "driversP/GPIO/GPIO.h"


static SemaphoreHandle_t xButtonSemaphore = NULL;
static SemaphoreHandle_t xButtonSemaphore2 = NULL;

SemaphoreHandle_t xRedLedSemaphore = NULL;
SemaphoreHandle_t xGreenLedSemaphore = NULL;
SemaphoreHandle_t xBlueLedSemaphore= NULL;

static void button_task_sw3(void *arg);
static void button_task_sw2(void *arg);
void red_led_toggle();
void green_led_toggle();
void blue_led_toggle();

void leds_init(){
		gpio_pin_config_t LED_RED_config = {
	        .pinDirection = kGPIO_DigitalOutput,
	        .outputLogic = 0U
	    };
        /* Initialize GPIO functionality on pin PTC9 (pin D7)  */
        GPIO_PinInit(GPIOC, 9u, &LED_RED_config);
        GPIO_PinInit(GPIOA, 11u, &LED_RED_config);
        GPIO_PinInit(GPIOE, 6u, &LED_RED_config);

        /* PORTC9 (pin D7) is configured as PTC9 */
        //Activarlos
        PORT_SetPinMux(PORTC, 9u, kPORT_MuxAsGpio);//rojo
        PORT_SetPinMux(PORTA, 11u, kPORT_MuxAsGpio);//azul
        PORT_SetPinMux(PORTE, 6u, kPORT_MuxAsGpio);//verde

        //Prender / Apagar
    	GPIO_PortToggle(GPIOC, 1u << 9u);
    	GPIO_PortToggle(GPIOA, 1u << 11u);
    	GPIO_PortToggle(GPIOE, 1u << 6u);

    	xRedLedSemaphore = xSemaphoreCreateBinary();
    	xGreenLedSemaphore = xSemaphoreCreateBinary();
    	xBlueLedSemaphore = xSemaphoreCreateBinary();

    	xTaskCreate(red_led_toggle, "RedLed", 256, NULL, 2, NULL);
    	xTaskCreate(green_led_toggle, "GreenLed", 256, NULL, 2, NULL);
    	xTaskCreate(blue_led_toggle, "BlueLed", 256, NULL, 2, NULL);

}

void button_driver_init()
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
			params->topic = "hoa/cuarto/boton";
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
			params->topic = "hoa/cuarto/boton";
			params->message = "comunicar";

			sys_thread_new("publish", pre_publish, (void *)params, 512, 3);
		}
	}
}

void data_received(char dato[]){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	if(strcmp(dato, "1")== 0 ){ //humo
		for(int i=0; i<4; i++){
	    	xSemaphoreGiveFromISR(xRedLedSemaphore, &xHigherPriorityTaskWoken);
	    	vTaskDelay(pdMS_TO_TICKS(200));  // Delay
		}
	} else if(strcmp(dato, "alguien")== 0){
		for(int i=0; i<4; i++){
	    	xSemaphoreGiveFromISR(xBlueLedSemaphore, &xHigherPriorityTaskWoken);
	    	vTaskDelay(pdMS_TO_TICKS(200));  // Delay
		}
	} else if(strcmp(dato, "presion alta")== 0 || strcmp(dato, "presion normal")== 0){
    	xSemaphoreGiveFromISR(xRedLedSemaphore, &xHigherPriorityTaskWoken);
    	xSemaphoreGiveFromISR(xBlueLedSemaphore, &xHigherPriorityTaskWoken);

	}else if(strcmp(dato, "posible caida")== 0){
		PRINTF("Se llamara a la ambulancia \r\n");
	}

	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void PORTA_IRQHandler(void) {
    // Limpiar la bandera de interrupción del pin PTA10 = sw3
    if (PORTA->ISFR & (1 << 10)) {
    	PORTA->ISFR |= (1 << 10); //limpiar bandera

    	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    	xSemaphoreGiveFromISR(xButtonSemaphore, &xHigherPriorityTaskWoken);
//    	xSemaphoreGiveFromISR(xGreenLedSemaphore, &xHigherPriorityTaskWoken);
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

void red_led_toggle()
{
	for (;;) {
		if (xSemaphoreTake(xRedLedSemaphore, portMAX_DELAY) == pdTRUE) {
			GPIO_PortToggle(GPIOC, 1u << 9u);
//			vTaskDelay(pdMS_TO_TICKS(10));  // Delay
		}
	}
}

void green_led_toggle()
{
	for (;;) {
		if (xSemaphoreTake(xGreenLedSemaphore, portMAX_DELAY) == pdTRUE) {
			GPIO_PortToggle(GPIOE, 1u << 6u);
//			vTaskDelay(pdMS_TO_TICKS(10));  // Delay
		}
	}
}

void blue_led_toggle()
{
	for (;;) {
		if (xSemaphoreTake(xBlueLedSemaphore, portMAX_DELAY) == pdTRUE) {
			GPIO_PortToggle(GPIOA, 1u << 11u);
//		    vTaskDelay(pdMS_TO_TICKS(10));  // Delay
		}
	}
}
