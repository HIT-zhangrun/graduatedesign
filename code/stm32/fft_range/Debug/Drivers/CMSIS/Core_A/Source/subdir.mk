################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.c 

OBJS += \
./Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.o 

C_DEPS += \
./Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Core_A/Source/%.o Drivers/CMSIS/Core_A/Source/%.su: ../Drivers/CMSIS/Core_A/Source/%.c Drivers/CMSIS/Core_A/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Core_A-2f-Source

clean-Drivers-2f-CMSIS-2f-Core_A-2f-Source:
	-$(RM) ./Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.d ./Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.o ./Drivers/CMSIS/Core_A/Source/irq_ctrl_gic.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Core_A-2f-Source

