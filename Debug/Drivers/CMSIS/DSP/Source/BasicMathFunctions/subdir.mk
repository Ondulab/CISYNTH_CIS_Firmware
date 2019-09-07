################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.c \
../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.o \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.d \
./Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_abs_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_add_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_dot_prod_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_mult_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_negate_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_offset_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_scale_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_shift_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_f32.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.o: ../Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' -DDEBUG_SAMPLE_RATE -D__FPU_PRESENT -DARM_MATH_CM7 '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Middleware/Inc" -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Peripheral/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"/mnt/data/Documents/Workspace_Cube/CISYNTH/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CMSIS/DSP/Source/BasicMathFunctions/arm_sub_q31.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

