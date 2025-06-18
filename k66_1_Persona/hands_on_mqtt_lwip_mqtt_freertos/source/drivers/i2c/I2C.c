/*
 * I2C.c
 *
 *  Created on: 4 abr. 2025
 *      Author: megae
 */
#include "Drivers/I2C/i2c.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define I2C_MASTER_CLK_SRC          I2C0_CLK_SRC
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)
#define EXAMPLE_I2C_MASTER_BASEADDR I2C0
#define WAIT_TIME                   10U

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU
#define I2C_BAUDRATE               100000U
#define I2C_DATA_LENGTH            33U

#define MPU6050_ADDRESS             0x68U       // Dirección del MPU6050 en I2C
#define MPU6050_ACCEL_XOUT_H        0x3BU       // Registro de aceleración en X (alto)
#define MPU6050_PWR_MGMT_1          0x6BU       // Registro de gestión de energía
#define I2C_BAUDRATE                100000U
#define GYRO_X_OUT_H 				0x43U
/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];

i2c_master_config_t masterConfig;

uint8_t accelData[6];
uint8_t gyroData[6];

int16_t accelX, accelY, accelZ,ax;
int16_t gyro_x, gyro_y, gyro_z,ax;
uint8_t current=0;
uint16_t valseco;

//typedef struct imu_data_tag imu_data_t;
QueueHandle_t IMU_Queue=NULL;


/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * brief: Enviar un byte a un registro especifico de un esclavo
 */
static void Write(uint8_t devAddr, uint8_t registerAddr, uint8_t data)
{

	 i2c_master_transfer_t masterXfer;
	 uint8_t txBuff[2] = {registerAddr, data};

	 memset(&masterXfer, 0, sizeof(masterXfer)); /*inicializar valores en 0 para evitar valores basura */
	 masterXfer.slaveAddress=devAddr;/*Asignar dirección de esclavo*/
	 masterXfer.direction=kI2C_Write;/*Se define como escritura*/
	 masterXfer.data=txBuff;/*Apuntar a txbuff que es el registro destino y el valor que se escribe*/
	 masterXfer.dataSize=sizeof(txBuff);/*Tamaño de los datos a transferir */
	 masterXfer.flags=kI2C_TransferDefaultFlag;/*Bandera default para la transferencia */
	 I2C_MasterTransferBlocking(I2C0, &masterXfer);/*Iniciar transferencia*/
}

/*
 * brief: Leer un registro dentro del esclavo
 */
static void Read(uint8_t devAddr, uint8_t registerAddr, uint8_t *data, size_t dataSize)
{
	i2c_master_transfer_t masterXfer;

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress= devAddr;/*Direccion esclavo*/
	masterXfer.direction=kI2C_Read;/*Modo lectura*/
	masterXfer.subaddress=registerAddr;/*Direccion primer registro a leer*/
	masterXfer.subaddressSize=1;				/*Tamaño de la subdireccion en bytes*/
	masterXfer.data=data;	/*Buffer con los datos almacenados */
	masterXfer.dataSize=dataSize;/*Bytes a leer*/
	masterXfer.flags=kI2C_TransferDefaultFlag;
	I2C_MasterTransferBlocking(I2C0, &masterXfer);
}
/*
 * brief: Juntar bytes alto y bajo en un solo valor
 */
static int16_t ConvertData(uint8_t msb, uint8_t lsb)
{
	return ((int16_t)(msb<<8)|lsb);

	/*Desplazar msb 8 a la izq para ocupar los más significativos */

}

/*
 * brief: seleccionar canal del mux de I2C,
 * En el caso de que se usen más muxes se puede cambiar en muxAddress
 */
static void SelectChannel(uint8_t muxAddress, uint8_t canal)
{
    uint8_t channel = (1 << canal);
    Write(muxAddress, 0x00, channel);
}

/*
 * brief: conversion de datos a valores de 0 a 99
 */

static int16_t Databien(int16_t original)
{
    if (original >= 0) {
    	if(original>=100)
    		original =99;
    	original= 50 + (original * 50 / 100);
        return original;

    } else {
    	if(original<=-100)
    		original=0;
        original= (original + 100) * 50 / 100;
        return original;
    }
}

/*
 * brief: obtener los valores de aceleración en x
 * se cambia de canal tambien
 */
void Send_XYZ(void)
{
	//PRINTF("Seleccionando canal: %d\r\n", current);
	SelectChannel(0x70, current);


	Read(0x68U,0x3BU,accelData,sizeof(accelData));/*Leer usando la función write*/
	imu_data_t data;

	data.accelX=accelX=ConvertData(accelData[0], accelData[1])/164;/*Datos en x*/
	data.accelY=accelY=ConvertData(accelData[2], accelData[3])/164;/*Datos en Y*/
	data.accelZ=accelZ=ConvertData(accelData[4], accelData[5])/164;/*Datos en Z*/


	//data.accelX= Databien(accelX);

    if (IMU_Queue != NULL) {
        xQueueSend(IMU_Queue, &data, pdMS_TO_TICKS(10));

    }

	current=(current+1)%5;

}


void XYZ_GYRO(){
	Read(0x68U,GYRO_X_OUT_H,gyroData,sizeof(gyroData));/*Leer usando la función write*/

	imu_data_t data;

		data.gyro_x=gyro_x=ConvertData(gyroData[0], gyroData[1])/164;/*Datos en x*/
		data.gyro_y=gyro_y=ConvertData(gyroData[2], gyroData[3])/164;/*Datos en Y*/
		data.gyro_z=gyro_z=ConvertData(gyroData[4], gyroData[5])/164;/*Datos en Z*/

		//data.accelX= Databien(accelX);
	    if (IMU_Queue != NULL) {
	        xQueueSend(IMU_Queue, &data, pdMS_TO_TICKS(600));

	    }

		//current=(current+1)%5;
}


/*
 * brief: inicializar I2C para los acelerometros
 */
void Accelerometer_Init()
{

	I2C_MasterGetDefaultConfig(&masterConfig);
	masterConfig.baudRate_Bps = I2C_BAUDRATE;
	I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));

	IMU_Queue = xQueueCreate(10, sizeof(imu_data_t));
	/*SelectChannel(0x70, 0); Setear la dirección del acelerómetro*/
	Write(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, 0x00);
/*	Write(0x68U, 0x6BU, 0x00); Activar accel, sacarlo de modo suspension*/


	//PRINTF("Inicializando MPU6050...\r\n");
}
