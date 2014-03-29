################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Benchmark/Benchmark.cpp \
../src/Benchmark/Seeker.cpp \
../src/Benchmark/Skippy.cpp \
../src/Benchmark/Zoned.cpp 

OBJS += \
./src/Benchmark/Benchmark.o \
./src/Benchmark/Seeker.o \
./src/Benchmark/Skippy.o \
./src/Benchmark/Zoned.o 

CPP_DEPS += \
./src/Benchmark/Benchmark.d \
./src/Benchmark/Seeker.d \
./src/Benchmark/Skippy.d \
./src/Benchmark/Zoned.d 


# Each subdirectory must supply rules for building sources it contributes
src/Benchmark/%.o: ../src/Benchmark/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -p -pedantic -pedantic-errors -w -Wall -Wextra -Werror -Wconversion -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


