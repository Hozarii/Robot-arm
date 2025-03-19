################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/UGUI/ugui.c \
../Lib/UGUI/ugui_button.c \
../Lib/UGUI/ugui_checkbox.c \
../Lib/UGUI/ugui_image.c \
../Lib/UGUI/ugui_progress.c \
../Lib/UGUI/ugui_sim.c \
../Lib/UGUI/ugui_sim_x11.c \
../Lib/UGUI/ugui_textbox.c 

OBJS += \
./Lib/UGUI/ugui.o \
./Lib/UGUI/ugui_button.o \
./Lib/UGUI/ugui_checkbox.o \
./Lib/UGUI/ugui_image.o \
./Lib/UGUI/ugui_progress.o \
./Lib/UGUI/ugui_sim.o \
./Lib/UGUI/ugui_sim_x11.o \
./Lib/UGUI/ugui_textbox.o 

C_DEPS += \
./Lib/UGUI/ugui.d \
./Lib/UGUI/ugui_button.d \
./Lib/UGUI/ugui_checkbox.d \
./Lib/UGUI/ugui_image.d \
./Lib/UGUI/ugui_progress.d \
./Lib/UGUI/ugui_sim.d \
./Lib/UGUI/ugui_sim_x11.d \
./Lib/UGUI/ugui_textbox.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/UGUI/%.o Lib/UGUI/%.su Lib/UGUI/%.cyclo: ../Lib/UGUI/%.c Lib/UGUI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-UGUI

clean-Lib-2f-UGUI:
	-$(RM) ./Lib/UGUI/ugui.cyclo ./Lib/UGUI/ugui.d ./Lib/UGUI/ugui.o ./Lib/UGUI/ugui.su ./Lib/UGUI/ugui_button.cyclo ./Lib/UGUI/ugui_button.d ./Lib/UGUI/ugui_button.o ./Lib/UGUI/ugui_button.su ./Lib/UGUI/ugui_checkbox.cyclo ./Lib/UGUI/ugui_checkbox.d ./Lib/UGUI/ugui_checkbox.o ./Lib/UGUI/ugui_checkbox.su ./Lib/UGUI/ugui_image.cyclo ./Lib/UGUI/ugui_image.d ./Lib/UGUI/ugui_image.o ./Lib/UGUI/ugui_image.su ./Lib/UGUI/ugui_progress.cyclo ./Lib/UGUI/ugui_progress.d ./Lib/UGUI/ugui_progress.o ./Lib/UGUI/ugui_progress.su ./Lib/UGUI/ugui_sim.cyclo ./Lib/UGUI/ugui_sim.d ./Lib/UGUI/ugui_sim.o ./Lib/UGUI/ugui_sim.su ./Lib/UGUI/ugui_sim_x11.cyclo ./Lib/UGUI/ugui_sim_x11.d ./Lib/UGUI/ugui_sim_x11.o ./Lib/UGUI/ugui_sim_x11.su ./Lib/UGUI/ugui_textbox.cyclo ./Lib/UGUI/ugui_textbox.d ./Lib/UGUI/ugui_textbox.o ./Lib/UGUI/ugui_textbox.su

.PHONY: clean-Lib-2f-UGUI

