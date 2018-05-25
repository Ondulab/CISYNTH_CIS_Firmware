################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o: ../Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Include"  -Og -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


