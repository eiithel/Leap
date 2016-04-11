################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/JsonObj.cpp \
../src/LeapEventListener.cpp \
../src/mosquitto.cpp 

OBJS += \
./src/Client.o \
./src/JsonObj.o \
./src/LeapEventListener.o \
./src/mosquitto.o 

CPP_DEPS += \
./src/Client.d \
./src/JsonObj.d \
./src/LeapEventListener.d \
./src/mosquitto.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/opt/LeapSDK/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


