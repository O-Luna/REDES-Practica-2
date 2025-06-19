/*
 * mqtt.h
 *
 *  Created on: 19 jun. 2025
 *      Author: armzr
 */

#ifndef ENET_H_
#define ENET_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <enet_cfg.h>
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_phy.h"
#include "mqtt_freertos.h"

#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/dhcp.h"
#include "lwip/netifapi.h"
#include "ethernetif.h"

#include "fsl_enet.h"
#include "fsl_reset.h"
#include "fsl_phyksz8081.h"

#include "rgb.h"

/* Ethernet configuration. */
extern phy_ksz8081_resource_t g_phy_resource;
#define EXAMPLE_ENET ENET

/* Address of PHY interface. */
#define EXAMPLE_PHY_ADDRESS 0x02U

/* PHY operations. */
#define EXAMPLE_PHY_OPS      &phyksz8081_ops
#define EXAMPLE_PHY_RESOURCE &g_phy_resource

/* ENET clock frequency. */
#define EXAMPLE_CLOCK_FREQ CLOCK_GetMainClkFreq()
/* Must be after include of app.h */
#ifndef configMAC_ADDR
#include "fsl_silicon_id.h"
#endif

#ifndef EXAMPLE_NETIF_INIT_FN
/*! @brief Network interface initialization function. */
#define EXAMPLE_NETIF_INIT_FN ethernetif0_init
#endif /* EXAMPLE_NETIF_INIT_FN */

/*! @brief Stack size of the temporary lwIP initialization thread. */
#define INIT_THREAD_STACKSIZE 1024

/*! @brief Priority of the temporary lwIP initialization thread. */
#define INIT_THREAD_PRIO DEFAULT_THREAD_PRIO

void stack_init(void *arg);
void BOARD_InitModuleClock(void);
void init_ENET(void);

#endif /* ENET_H_ */
