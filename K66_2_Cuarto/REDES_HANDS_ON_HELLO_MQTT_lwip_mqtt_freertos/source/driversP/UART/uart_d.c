#include "driversP/mqtt/mqtt.h"
#include "driversP/GPIO/GPIO.h"
#include "driversP/UART/uart_d.h"
#include "driversP/UART/uart_d_cfg.h"
#include "fsl_uart.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include <stdbool.h>
#include <stdio.h>

bool UART_ReadByte_NonBlocking(UART_Type *base, char *c);
void uart_listener_task(void *pvParameters);

void uart_init(void) {
    // Configuración de la UART de depuración
    uart_config_t config;
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200;
    config.enableTx = true;
    config.enableRx = true;

    UART_Init(DEBUG_UART, &config, CLOCK_GetFreq(DEBUG_UART_CLKSRC));

    // Crear tarea para escuchar la UART
    sys_thread_new("uart", uart_listener_task, NULL, 512, 3);
}

// Función para lectura no bloqueante con verificación
bool UART_ReadByte_NonBlocking(UART_Type *base, char *c) {
    if (UART_GetStatusFlags(base) & kUART_RxDataRegFullFlag) {
        *c = UART_ReadByte(base);  // Función inline del SDK
        return true;
    }
    return false;
}

void uart_listener_task(void *pvParameters) {
    char uart_buffer[UART_BUFFER_SIZE];
    int index = 0;
    char c;

    while (1) {
        // Espera a recibir un carácter por UART
        if (UART_ReadByte_NonBlocking(DEBUG_UART, &c)) {
            // Echo del carácter recibido (opcional)
            UART_WriteByte(DEBUG_UART, (uint8_t)c);

            if (c == '\n' || c == '\r' || index >= UART_BUFFER_SIZE - 1) {
                if (index > 0) {  // Solo procesar si hay datos
                    uart_buffer[index] = '\0';  // Termina el string

                    // Reserva memoria para los parámetros
                    mqtt_args_t *params = pvPortMalloc(sizeof(mqtt_args_t));
                    if (params != NULL) {
                        params->topic = "hoa/cuarto/prueba";

                        // Reserva memoria para el mensaje
                        char *msg = pvPortMalloc(strlen(uart_buffer) + 1);
                        if (msg != NULL) {
                            strcpy(msg, uart_buffer);
                            params->message = msg;

                            // Crea la tarea para publicar
                            sys_thread_new("publish", pre_publish, (void *)params, 512, 3);
                        } else {
                            vPortFree(params);
                        }
                    }
                }
                index = 0;  // Reinicia el buffer
            } else {
                uart_buffer[index++] = c;
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));  // Pequeño delay para evitar saturar CPU
    }
}
