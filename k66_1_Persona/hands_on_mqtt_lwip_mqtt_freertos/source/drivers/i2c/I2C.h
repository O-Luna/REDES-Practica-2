/*
 * I2C.h
 *
 *  Created on: 4 abr. 2025
 *      Author: megae
 */
#include <string.h>
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
//#include "Drivers/PIT/pit_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#ifndef DRIVERS_I2C_I2C_H_
#define DRIVERS_I2C_I2C_H_

void Accelerometer_Init();
void Send_XYZ(void);
void XYZ_GYRO();

typedef struct{
	int16_t accelX;
	int16_t accelY;
	int16_t accelZ;
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;

}imu_data_t;

extern QueueHandle_t IMU_Queue;
int16_t extern accelX, accelY, accelZ;

#endif /* DRIVERS_I2C_I2C_H_ */
