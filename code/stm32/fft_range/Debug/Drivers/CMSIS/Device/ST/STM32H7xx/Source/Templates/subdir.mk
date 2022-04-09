################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.c \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.c \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.c \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.c \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.o \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.o \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.o \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.o \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.d \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.d \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.d \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.d \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.o Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.su: ../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.c Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM7 -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates

clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates:
	-$(RM) ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.su ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_boot_cm4_cm7.su ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm4_cm7gated.su ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_dualcore_bootcm7_cm4gated.su ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx_singlecore.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates

