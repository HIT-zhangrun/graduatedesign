################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/startup_ARMCM4.s 

C_SRCS += \
../Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.c 

OBJS += \
./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/startup_ARMCM4.o \
./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.o 

S_DEPS += \
./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/startup_ARMCM4.d 

C_DEPS += \
./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/%.o: ../Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/%.s Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/%.o Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/%.su: ../Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/%.c Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-NN-2f-Examples-2f-ARM-2f-arm_nn_examples-2f-gru-2f-RTE-2f-Device-2f-ARMCM4_FP

clean-Drivers-2f-CMSIS-2f-NN-2f-Examples-2f-ARM-2f-arm_nn_examples-2f-gru-2f-RTE-2f-Device-2f-ARMCM4_FP:
	-$(RM) ./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/startup_ARMCM4.d ./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/startup_ARMCM4.o ./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.d ./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.o ./Drivers/CMSIS/NN/Examples/ARM/arm_nn_examples/gru/RTE/Device/ARMCM4_FP/system_ARMCM4.su

.PHONY: clean-Drivers-2f-CMSIS-2f-NN-2f-Examples-2f-ARM-2f-arm_nn_examples-2f-gru-2f-RTE-2f-Device-2f-ARMCM4_FP

