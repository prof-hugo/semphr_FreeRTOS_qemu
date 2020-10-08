################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/diag/Trace.c \
../system/src/diag/trace_impl.c 

OBJS += \
./system/src/diag/Trace.o \
./system/src/diag/trace_impl.o 

C_DEPS += \
./system/src/diag/Trace.d \
./system/src/diag/trace_impl.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/diag/%.o: ../system/src/diag/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DSTM32F407xx -DUSE_HAL_DRIVER -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\Libraries\CMSIS\Core\Include" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\Libraries\CMSIS\Device\ST\STM32F4xx\Include" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\Libraries\STM32F4xx_HAL_Driver\Inc" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\FreeRTOS\Source\include" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\FreeRTOS\Source\portable\GCC\ARM_CM3" -I"C:\Users\hviei\eclipse-workspace\semphr_FreeRTOS_qemu2\system\inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


