################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../SousVide.ino 

CPP_SRCS += \
../.ino.cpp 

LINK_OBJ += \
./.ino.cpp.o 

INO_DEPS += \
./SousVide.ino.d 

CPP_DEPS += \
./.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/standard" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/SPI" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/SPI/src" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Servo/1.1.1" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Servo/1.1.1/src" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/dallas-temperature-control" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/LiquidTWI2-v110" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/OneWire-master" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/PID" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/PID_AutoTune_v0" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/EEPROM" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/EEPROM/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

SousVide.o: ../SousVide.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-g++" -c -g -Os -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/cores/arduino" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/variants/standard" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/Wire/src" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/SPI" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/SPI/src" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Servo/1.1.1" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Servo/1.1.1/src" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/dallas-temperature-control" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/LiquidTWI2-v110" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/OneWire-master" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/PID" -I"/Users/patrickstrobel/Documents/workspace/SousVide/libraries/PID_AutoTune_v0" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/EEPROM" -I"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.6.14/libraries/EEPROM/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


