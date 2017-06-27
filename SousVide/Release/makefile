################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/dallas-temperature-control/subdir.mk
-include libraries/Wire/src/utility/subdir.mk
-include libraries/Wire/src/subdir.mk
-include libraries/Servo/src/samd/subdir.mk
-include libraries/Servo/src/sam/subdir.mk
-include libraries/Servo/src/avr/subdir.mk
-include libraries/SPI/src/subdir.mk
-include libraries/PID_AutoTune_v0/subdir.mk
-include libraries/PID/subdir.mk
-include libraries/OneWire-master/subdir.mk
-include libraries/LiquidTWI2-v110/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
SousVide.elf \

EEP += \
SousVide.eep \

FLASH_IMAGE += \
SousVide.hex \


# All Target
all: SousVide

# Tool invocations
SousVide: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-size" -A "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-gcc-ar" rcs  "/Users/patrickstrobel/Documents/workspace/SousVide/Release/arduino.ar"    arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

SousVide.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-gcc" -Os -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p  -o "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.elf"   $(LINK_OBJ) $(AR)    "-L/Users/patrickstrobel/Documents/workspace/SousVide/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

SousVide.eep: $(ELF)
	@echo 'Create eeprom image'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.elf" "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.eep"
	@echo 'Finished building: $@'
	@echo ' '

SousVide.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/Users/patrickstrobel/Downloads/Eclipse.app/Contents/Eclipse/arduinoPlugin/tools/arduino/avr-gcc/4.9.2-atmel3.5.3-arduino2/bin/avr-objcopy" -O ihex -R .eeprom  "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.elf" "/Users/patrickstrobel/Documents/workspace/SousVide/Release/SousVide.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) SousVide
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
