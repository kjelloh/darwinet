################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CommandLineProcessor.cpp \
../src/DarwinetDomainProxy.cpp \
../src/DarwinetEngineProxy.cpp \
../src/DarwinetMIVProxy.cpp \
../src/DarwinetViewProxy.cpp \
../src/MIVConsoleCygwin.cpp 

OBJS += \
./src/CommandLineProcessor.o \
./src/DarwinetDomainProxy.o \
./src/DarwinetEngineProxy.o \
./src/DarwinetMIVProxy.o \
./src/DarwinetViewProxy.o \
./src/MIVConsoleCygwin.o 

CPP_DEPS += \
./src/CommandLineProcessor.d \
./src/DarwinetDomainProxy.d \
./src/DarwinetEngineProxy.d \
./src/DarwinetMIVProxy.d \
./src/DarwinetViewProxy.d \
./src/MIVConsoleCygwin.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


