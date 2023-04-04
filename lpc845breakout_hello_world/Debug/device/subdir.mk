################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_LPC845.c 

C_DEPS += \
./device/system_LPC845.d 

OBJS += \
./device/system_LPC845.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_LPC845M301JBD48 -DMCUXPRESSO_SDK -DCPU_LPC845M301JBD48_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\source" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\littleshell" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\drivers" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\device" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\component\uart" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\utilities" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\CMSIS" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\lpc845breakout\demo_apps\hello_world" -I"D:\work\localhost\LPC845\lpc845breakout_hello_world\board" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_LPC845.d ./device/system_LPC845.o

.PHONY: clean-device

