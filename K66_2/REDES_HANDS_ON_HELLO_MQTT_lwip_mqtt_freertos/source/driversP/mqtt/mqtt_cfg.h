/*
 * mqtt_cfg.h
 *
 *  Created on: 15 jun. 2025
 *      Author: oralu
 */

#ifndef DRIVERSP_MQTT_MQTT_CFG_H_
#define DRIVERSP_MQTT_MQTT_CFG_H_

/* MAC address configuration. */
#ifndef configMAC_ADDR
#define configMAC_ADDR                     \
    {                                      \
        0x02, 0x12, 0x13, 0x11, 0x14, 0x15 \
    }
#endif

/*! @brief MQTT server host name or IP address. */
#define EXAMPLE_MQTT_SERVER_HOST "broker.hivemq.com"

/*! @brief MQTT server port number. */
#define EXAMPLE_MQTT_SERVER_PORT 1883

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define INIT_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_THREAD_PRIO DEFAULT_THREAD_PRIO

/*! @brief Stack size of the temporary initialization thread. */
#define APP_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary initialization thread. */
#define APP_THREAD_PRIO DEFAULT_THREAD_PRIO

#endif /* DRIVERSP_MQTT_MQTT_CFG_H_ */
