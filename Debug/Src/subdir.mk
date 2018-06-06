################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/cis.c \
../Src/dac.c \
../Src/dma.c \
../Src/gpio.c \
../Src/hrtim.c \
../Src/main.c \
../Src/stm32h7xx_hal_msp.c \
../Src/stm32h7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32h7xx.c \
../Src/tim.c \
../Src/usart.c \
../Src/usb_otg.c 

OBJS += \
./Src/adc.o \
./Src/cis.o \
./Src/dac.o \
./Src/dma.o \
./Src/gpio.o \
./Src/hrtim.o \
./Src/main.o \
./Src/stm32h7xx_hal_msp.o \
./Src/stm32h7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32h7xx.o \
./Src/tim.o \
./Src/usart.o \
./Src/usb_otg.o 

C_DEPS += \
./Src/adc.d \
./Src/cis.d \
./Src/dac.d \
./Src/dma.d \
./Src/gpio.d \
./Src/hrtim.d \
./Src/main.d \
./Src/stm32h7xx_hal_msp.d \
./Src/stm32h7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32h7xx.d \
./Src/tim.d \
./Src/usart.d \
./Src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Device/ST/STM32H7xx/Include" -I"/mnt/Data/Documents/Workspace_AC6/CIS_H7/Drivers/CMSIS/Include"  -Og -g -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


