################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/driversP/mqtt/matt.c 

C_DEPS += \
./source/driversP/mqtt/matt.d 

OBJS += \
./source/driversP/mqtt/matt.o 


# Each subdirectory must supply rules for building sources it contributes
source/driversP/mqtt/%.o: ../source/driversP/mqtt/%.c source/driversP/mqtt/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -D_POSIX_SOURCE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K66F -DFREEDOM -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\source" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\mdio" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\phy" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\lwip\src\include\lwip\apps" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\lwip\port" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\lwip\src" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\lwip\src\include" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\drivers" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\utilities" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\device" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\component\uart" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\component\serial_manager" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\component\lists" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\CMSIS" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\freertos\freertos_kernel\include" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Embebidosk64\WORKSPACE_REDES\REDES_HANDS_ON_HELLO_MQTT_lwip_mqtt_freertos\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-driversP-2f-mqtt

clean-source-2f-driversP-2f-mqtt:
	-$(RM) ./source/driversP/mqtt/matt.d ./source/driversP/mqtt/matt.o

.PHONY: clean-source-2f-driversP-2f-mqtt

