################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FFT/fft.c 

OBJS += \
./FFT/fft.o 

C_DEPS += \
./FFT/fft.d 


# Each subdirectory must supply rules for building sources it contributes
FFT/%.o FFT/%.su: ../FFT/%.c FFT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H750xx -D__TARGET_FPU_VFP -c -I../FFT -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"C:/Users/zhangrun/OneDrive/my_doc/project/graduate_design/graduatedesign/code/stm32/fft_process/CMSIS_DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FFT

clean-FFT:
	-$(RM) ./FFT/fft.d ./FFT/fft.o ./FFT/fft.su

.PHONY: clean-FFT

