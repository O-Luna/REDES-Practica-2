################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/drivers/gpio/GPIO.c 

C_DEPS += \
./source/drivers/gpio/GPIO.d 

OBJS += \
./source/drivers/gpio/GPIO.o 


# Each subdirectory must supply rules for building sources it contributes
source/drivers/gpio/%.o: ../source/drivers/gpio/%.c source/drivers/gpio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK66FN2M0VMD18 -DCPU_MK66FN2M0VMD18_cm4 -D_POSIX_SOURCE -DUSE_RTOS=1 -DPRINTF_ADVANCED_ENABLE=1 -DFRDM_K66F -DFREEDOM -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\source" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\mdio" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\phy" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\lwip\src\include\lwip\apps" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\lwip\port" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\lwip\src" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\lwip\src\include" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\drivers" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\utilities" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\device" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\component\uart" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\component\serial_manager" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\component\lists" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\CMSIS" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\freertos\freertos_kernel\include" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Enrique\SisOperativo\hands_on_mqtt_lwip_mqtt_freertos\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-drivers-2f-gpio

clean-source-2f-drivers-2f-gpio:
	-$(RM) ./source/drivers/gpio/GPIO.d ./source/drivers/gpio/GPIO.o

.PHONY: clean-source-2f-drivers-2f-gpio

