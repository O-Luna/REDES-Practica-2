#include "driversP/mqtt/mqtt.h"
#include "driversP/GPIO/GPIO.h"

#include "stdio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"



int main(void)
{
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();


    button_driver_init();
    mqtt_init();

    vTaskStartScheduler();

    return 0;
}
//#endif
