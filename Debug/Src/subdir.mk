################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/004spi_tx_test.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/004spi_tx_test.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/004spi_tx_test.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I"C:/Users/umurd/Desktop/MCU1/stm32f4xx_drivers/drivers/Inc" -I"C:/Users/umurd/Desktop/MCU1/stm32f4xx_drivers/bsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

