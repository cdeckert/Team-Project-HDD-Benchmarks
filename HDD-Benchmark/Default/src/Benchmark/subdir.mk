################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Benchmark/Benchmark.cpp \
../src/Benchmark/Skippy.cpp 

OBJS += \
./src/Benchmark/Benchmark.o \
./src/Benchmark/Skippy.o 

CPP_DEPS += \
./src/Benchmark/Benchmark.d \
./src/Benchmark/Skippy.d 


# Each subdirectory must supply rules for building sources it contributes
src/Benchmark/%.o: ../src/Benchmark/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/chris/Team-Project-HDD-Benchmarks/HDD-Benchmark/src/Benchmark" -I"/home/chris/Team-Project-HDD-Benchmarks/HDD-Benchmark/src" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


