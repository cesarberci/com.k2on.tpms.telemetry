################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DBDataExanger.cpp \
../src/TelemetrySender.cpp \
../src/utils.cpp 

OBJS += \
./src/DBDataExanger.o \
./src/TelemetrySender.o \
./src/utils.o 

CPP_DEPS += \
./src/DBDataExanger.d \
./src/TelemetrySender.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


