################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/uart/fsl_adapter_miniusart.c 

C_DEPS += \
./component/uart/fsl_adapter_miniusart.d 

OBJS += \
./component/uart/fsl_adapter_miniusart.o 


# Each subdirectory must supply rules for building sources it contributes
component/uart/%.o: ../component/uart/%.c component/uart/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_LPC845M301JBD48 -DMCUXPRESSO_SDK -DCPU_LPC845M301JBD48_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\source" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\drivers" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\device" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\component\uart" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\utilities" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\CMSIS" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\lpc845breakout\demo_apps\hello_world" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\board" -Os -fno-common -g -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-uart

clean-component-2f-uart:
	-$(RM) ./component/uart/fsl_adapter_miniusart.d ./component/uart/fsl_adapter_miniusart.o

.PHONY: clean-component-2f-uart

