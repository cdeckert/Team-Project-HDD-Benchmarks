################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Benchmark.cpp \
../src/ResultSaver.cpp \
../src/Seeker.cpp \
../src/SizeConverter.cpp \
../src/Skippy.cpp \
../src/Stopwatch.cpp \
../src/Zoned.cpp \
../src/main.cpp 

OBJS += \
./src/Benchmark.o \
./src/ResultSaver.o \
./src/Seeker.o \
./src/SizeConverter.o \
./src/Skippy.o \
./src/Stopwatch.o \
./src/Zoned.o \
./src/main.o 

CPP_DEPS += \
./src/Benchmark.d \
./src/ResultSaver.d \
./src/Seeker.d \
./src/SizeConverter.d \
./src/Skippy.d \
./src/Stopwatch.d \
./src/Zoned.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


