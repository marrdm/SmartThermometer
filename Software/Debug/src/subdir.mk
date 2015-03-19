################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SPI.c \
../src/Software.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/pwm.c \
../src/uart.c 

OBJS += \
./src/SPI.o \
./src/Software.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/pwm.o \
./src/uart.o 

C_DEPS += \
./src/SPI.d \
./src/Software.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/pwm.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSISv2p00_LPC11xx -D__LPC11XX__ -D__REDLIB__ -I"C:\Users\jeffrey\Documents\E7020E\SmartThermometer\CMSISv2p00_LPC11xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


