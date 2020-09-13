################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/user/Development/NavigationPlatform/src/driver.cpp \
/home/user/Development/NavigationPlatform/src/main.cpp \
/home/user/Development/NavigationPlatform/src/receiver.cpp \
/home/user/Development/NavigationPlatform/src/rover.cpp 

OBJS += \
./driver.o \
./main.o \
./receiver.o \
./rover.o 

CPP_DEPS += \
./driver.d \
./main.d \
./receiver.d \
./rover.d 


# Each subdirectory must supply rules for building sources it contributes
driver.o: /home/user/Development/NavigationPlatform/src/driver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.o: /home/user/Development/NavigationPlatform/src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

receiver.o: /home/user/Development/NavigationPlatform/src/receiver.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

rover.o: /home/user/Development/NavigationPlatform/src/rover.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


