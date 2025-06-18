#include "driversP/UART/uart_d.h"

bool UART_ReadByte_NonBlocking(UART_Type *base, char *c);
void uart_listener_task(void *pvParameters);

void uart_init(void) {
    // config de uart
    uart_config_t config;
    UART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200;
    config.enableTx = true;
    config.enableRx = true;

    UART_Init(DEBUG_UART, &config, CLOCK_GetFreq(DEBUG_UART_CLKSRC));

    // task para escuchar la UART
    sys_thread_new("uart", uart_listener_task, NULL, 512, 3);
}

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
        // Esperar a recibir un carácter por UART
        if (UART_ReadByte_NonBlocking(DEBUG_UART, &c)) {
            // echo del carácter recibido
            UART_WriteByte(DEBUG_UART, (uint8_t)c);

            if (c == '\n' || c == '\r' || index >= UART_BUFFER_SIZE - 1) {
                if (index > 0) {
                    uart_buffer[index] = '\0';  // fin del string

                    // reservar memoria para los parámetros
                    mqtt_args_t *params = pvPortMalloc(sizeof(mqtt_args_t));
                    if (params != NULL) {
                        params->topic = "hoa/cuarto/prueba";

                        // reservar memoria para el mensaje
                        char *msg = pvPortMalloc(strlen(uart_buffer) + 1);
                        if (msg != NULL) {
                            strcpy(msg, uart_buffer);
                            params->message = msg;

                            // task para publicar
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

        vTaskDelay(pdMS_TO_TICKS(10));  // Delay
    }
}
