################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Communication.cpp \
../src/DigitalIO.cpp \
../src/Log.cpp \
../src/Observeble.cpp \
../src/Observer.cpp \
../src/SQLReader.cpp \
../src/StringTools.cpp \
../src/TpmsData.cpp \
../src/TpmsDevice.cpp \
../src/TpmsHandShake.cpp \
../src/TpmsRawData.cpp \
../src/TpmsTireData.cpp \
../src/utils.cpp 

OBJS += \
./src/Communication.o \
./src/DigitalIO.o \
./src/Log.o \
./src/Observeble.o \
./src/Observer.o \
./src/SQLReader.o \
./src/StringTools.o \
./src/TpmsData.o \
./src/TpmsDevice.o \
./src/TpmsHandShake.o \
./src/TpmsRawData.o \
./src/TpmsTireData.o \
./src/utils.o 

CPP_DEPS += \
./src/Communication.d \
./src/DigitalIO.d \
./src/Log.d \
./src/Observeble.d \
./src/Observer.d \
./src/SQLReader.d \
./src/StringTools.d \
./src/TpmsData.d \
./src/TpmsDevice.d \
./src/TpmsHandShake.d \
./src/TpmsRawData.d \
./src/TpmsTireData.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\cesar\eclipse-workspace\rapidjson\include" -I"C:\Users\cesar\eclipse-workspace\curl-7.65.1-win64-mingw\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


