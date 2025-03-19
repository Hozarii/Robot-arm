################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/Src/communication.c \
../Lib/Src/image.c \
../Lib/Src/lcd.c \
../Lib/Src/led_ring.c 

OBJS += \
./Lib/Src/communication.o \
./Lib/Src/image.o \
./Lib/Src/lcd.o \
./Lib/Src/led_ring.o 

C_DEPS += \
./Lib/Src/communication.d \
./Lib/Src/image.d \
./Lib/Src/lcd.d \
./Lib/Src/led_ring.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/Src/%.o Lib/Src/%.su Lib/Src/%.cyclo: ../Lib/Src/%.c Lib/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-Src

clean-Lib-2f-Src:
	-$(RM) ./Lib/Src/communication.cyclo ./Lib/Src/communication.d ./Lib/Src/communication.o ./Lib/Src/communication.su ./Lib/Src/image.cyclo ./Lib/Src/image.d ./Lib/Src/image.o ./Lib/Src/image.su ./Lib/Src/lcd.cyclo ./Lib/Src/lcd.d ./Lib/Src/lcd.o ./Lib/Src/lcd.su ./Lib/Src/led_ring.cyclo ./Lib/Src/led_ring.d ./Lib/Src/led_ring.o ./Lib/Src/led_ring.su

.PHONY: clean-Lib-2f-Src

