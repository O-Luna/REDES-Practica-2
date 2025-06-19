/*
 * mqtt.c
 *
 *  Created on: 19 jun. 2025
 *      Author: armzr
 */
#include <enet.h>

phy_ksz8081_resource_t g_phy_resource;

static phy_handle_t phyHandle;

void BOARD_InitModuleClock(void)
{
    /* Set 50MHz output clock required by PHY. */
    CLOCK_EnableClock(kCLOCK_TddrMciEnetClk);
}

static void MDIO_Init(void)
{
    uint32_t i = ENET_GetInstance(EXAMPLE_ENET);

    (void)CLOCK_EnableClock(s_enetClock[i]);
    (void)CLOCK_EnableClock(s_enetExtraClock[i]);
    ENET_SetSMI(EXAMPLE_ENET, EXAMPLE_CLOCK_FREQ, false);
}

static status_t MDIO_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(EXAMPLE_ENET, phyAddr, regAddr, data);
}

static status_t MDIO_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(EXAMPLE_ENET, phyAddr, regAddr, pData);
}

/*!
 * @brief Initializes lwIP stack.
 *
 * @param arg unused
 */
void stack_init(void *arg)
{
    static struct netif netif;
    ethernetif_config_t enet_config = {
        .phyHandle   = &phyHandle,
        .phyAddr     = EXAMPLE_PHY_ADDRESS,
        .phyOps      = EXAMPLE_PHY_OPS,
        .phyResource = EXAMPLE_PHY_RESOURCE,
        .srcClockHz  = EXAMPLE_CLOCK_FREQ,
#ifdef configMAC_ADDR
        .macAddress = configMAC_ADDR,
#endif
    };

    LWIP_UNUSED_ARG(arg);

    /* Set MAC address. */
#ifndef configMAC_ADDR
    (void)SILICONID_ConvertToMacAddr(&enet_config.macAddress);
#endif

    tcpip_init(NULL, NULL);

    netifapi_netif_add(&netif, NULL, NULL, NULL, &enet_config, EXAMPLE_NETIF_INIT_FN, tcpip_input);
    netifapi_netif_set_default(&netif);
    netifapi_netif_set_up(&netif);

    netifapi_dhcp_start(&netif);

    PRINTF("\r\n************************************************\r\n");
    PRINTF(" MQTT client example\r\n");
    PRINTF("************************************************\r\n");

    while (ethernetif_wait_linkup(&netif, 5000) != ERR_OK)
    {
        PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
    }

    /* Wait for address from DHCP */

    PRINTF("Getting IP address from DHCP...\r\n");

    (void)ethernetif_wait_ipv4_valid(&netif, ETHERNETIF_WAIT_FOREVER);

    mqtt_freertos_run_thread(&netif);

    vTaskDelete(NULL);
}

void init_ENET(void)
{
	gpio_pin_config_t gpio_config = {kGPIO_DigitalOutput, 1U};

	ENET_ResetHardware();

	GPIO_PortInit(GPIO, 0U);
	GPIO_PortInit(GPIO, 1U);

	GPIO_PinInit(GPIO, 0U, 21U, &gpio_config); /* ENET_RST */
	gpio_config.pinDirection = kGPIO_DigitalInput;
	gpio_config.outputLogic  = 0U;
	GPIO_PinInit(GPIO, 1U, 23U, &gpio_config); /* ENET_INT */

	GPIO_PinWrite(GPIO, 0U, 21U, 0U);
	SDK_DelayAtLeastUs(1000000, CLOCK_GetCoreSysClkFreq());
	GPIO_PinWrite(GPIO, 0U, 21U, 1U);

	MDIO_Init();
	g_phy_resource.read  = MDIO_Read;
	g_phy_resource.write = MDIO_Write;
}
