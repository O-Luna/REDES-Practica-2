#include "driversP/mqtt/mqtt.h"
#include "driversP/GPIO/GPIO.h"
#include "driversP/UART/uart_d.h"

#include "stdio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

//void prueba(){
//
////	char data[5]= {'a', 'y', 'u', 'd', 'a'};
//	char data[10]= {'m', 'o', 'v', 'i', 'm', 'i', 'e', 'n', 't', 'o'};
////	char data[3]= {'g', 'a', 's'};
//    char dato[32]= "";
//
//    for(int i=0; i<10; i++){
//    	char temp[2] = {data[i], '\0'};
//        strcat(dato, temp);
//    }
////    data_received("ayuda");
//	data_received(dato);
//    vTaskDelete(NULL);
//}

int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();


    button_driver_init();
    mqtt_init();
    uart_init();
    leds_init();

//	xTaskCreate(prueba, "Prueba", 256, NULL, 2, NULL);

    vTaskStartScheduler();

    return 0;
}
//#endif
