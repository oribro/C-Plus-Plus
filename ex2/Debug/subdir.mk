################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FileReader.cpp \
../InstrumentalSong.cpp \
../LyricalSong.cpp \
../MIR.cpp \
../Parameters.cpp \
../Song.cpp \
../SortHelper.cpp 

O_SRCS += \
../FileReader.o \
../InstrumentalSong.o \
../LyricalSong.o \
../MIR.o \
../Parameters.o \
../Song.o \
../SortHelper.o 

OBJS += \
./FileReader.o \
./InstrumentalSong.o \
./LyricalSong.o \
./MIR.o \
./Parameters.o \
./Song.o \
./SortHelper.o 

CPP_DEPS += \
./FileReader.d \
./InstrumentalSong.d \
./LyricalSong.d \
./MIR.d \
./Parameters.d \
./Song.d \
./SortHelper.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -Wextra -std=c++11 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


