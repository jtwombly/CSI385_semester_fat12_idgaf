################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fat.c \
../fatSupport.c \
../pbs.c \
../pfe.c \
../shell_code.c 

OBJS += \
./fat.o \
./fatSupport.o \
./pbs.o \
./pfe.o \
./shell_code.o 

C_DEPS += \
./fat.d \
./fatSupport.d \
./pbs.d \
./pfe.d \
./shell_code.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


