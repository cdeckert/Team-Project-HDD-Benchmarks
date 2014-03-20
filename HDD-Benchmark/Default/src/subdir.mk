################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ResultSaver.cpp \
../src/Stopwatch.cpp \
../src/main.cpp 

OBJS += \
./src/ResultSaver.o \
./src/Stopwatch.o \
./src/main.o 

CPP_DEPS += \
./src/ResultSaver.d \
./src/Stopwatch.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/chris/Team-Project-HDD-Benchmarks/HDD-Benchmark/src/Benchmark" -I"/home/chris/Team-Project-HDD-Benchmarks/HDD-Benchmark/src" -O2 -g -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


