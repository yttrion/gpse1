################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/bsp/stm32f1_adc.c \
../lib/bsp/stm32f1_extit.c \
../lib/bsp/stm32f1_flash.c \
../lib/bsp/stm32f1_gpio.c \
../lib/bsp/stm32f1_i2c.c \
../lib/bsp/stm32f1_motorDC.c \
../lib/bsp/stm32f1_pwm.c \
../lib/bsp/stm32f1_rtc.c \
../lib/bsp/stm32f1_sd.c \
../lib/bsp/stm32f1_spi.c \
../lib/bsp/stm32f1_sys.c \
../lib/bsp/stm32f1_timer.c \
../lib/bsp/stm32f1_uart.c \
../lib/bsp/stm32f1_weak_it.c \
../lib/bsp/stm32f1xx_nucleo.c \
../lib/bsp/system_stm32f1xx.c \
../lib/bsp/systick.c 

OBJS += \
./lib/bsp/stm32f1_adc.o \
./lib/bsp/stm32f1_extit.o \
./lib/bsp/stm32f1_flash.o \
./lib/bsp/stm32f1_gpio.o \
./lib/bsp/stm32f1_i2c.o \
./lib/bsp/stm32f1_motorDC.o \
./lib/bsp/stm32f1_pwm.o \
./lib/bsp/stm32f1_rtc.o \
./lib/bsp/stm32f1_sd.o \
./lib/bsp/stm32f1_spi.o \
./lib/bsp/stm32f1_sys.o \
./lib/bsp/stm32f1_timer.o \
./lib/bsp/stm32f1_uart.o \
./lib/bsp/stm32f1_weak_it.o \
./lib/bsp/stm32f1xx_nucleo.o \
./lib/bsp/system_stm32f1xx.o \
./lib/bsp/systick.o 

C_DEPS += \
./lib/bsp/stm32f1_adc.d \
./lib/bsp/stm32f1_extit.d \
./lib/bsp/stm32f1_flash.d \
./lib/bsp/stm32f1_gpio.d \
./lib/bsp/stm32f1_i2c.d \
./lib/bsp/stm32f1_motorDC.d \
./lib/bsp/stm32f1_pwm.d \
./lib/bsp/stm32f1_rtc.d \
./lib/bsp/stm32f1_sd.d \
./lib/bsp/stm32f1_spi.d \
./lib/bsp/stm32f1_sys.d \
./lib/bsp/stm32f1_timer.d \
./lib/bsp/stm32f1_uart.d \
./lib/bsp/stm32f1_weak_it.d \
./lib/bsp/stm32f1xx_nucleo.d \
./lib/bsp/system_stm32f1xx.d \
./lib/bsp/systick.d 


# Each subdirectory must supply rules for building sources it contributes
lib/bsp/%.o: ../lib/bsp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32F1 -DNUCLEO_F103RB -DSTM32F103RBTx -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/pierr/Desktop/gpse1/lib/bsp" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/VL53L0X" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/MPU6050" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/Common" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/hts221" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/lis3mdl" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/lps22hb" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/lps25hb" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/lsm6ds0" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/iks01a1/lsm6ds3" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/tft_ili9341" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/tft_pcd8544" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/MCP23S17" -I"C:/Users/pierr/Desktop/gpse1/lib/hal/inc" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/Common" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/lcd2x16" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/MLX90614" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/MatrixKeyboard" -I"C:/Users/pierr/Desktop/gpse1/lib/bsp/MatrixLed" -I"C:/Users/pierr/Desktop/gpse1/lib/CMSIS/core" -I"C:/Users/pierr/Desktop/gpse1/lib/CMSIS/device" -I"C:/Users/pierr/Desktop/gpse1/lib/middleware/FatFs" -I"C:/Users/pierr/Desktop/gpse1/lib/middleware/FatFs/src" -I"C:/Users/pierr/Desktop/gpse1/lib/middleware/FatFs/src/drivers" -I"C:/Users/pierr/Desktop/gpse1/appli"  -Og -g3 -Wall -Wextra -Wconversion -fmessage-length=0 -ffunction-sections -fdata-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


