################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Include"  -O3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


