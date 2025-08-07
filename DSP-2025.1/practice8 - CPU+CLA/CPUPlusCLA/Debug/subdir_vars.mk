################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2837xD_RAM_CLA_lnk_cpu1.cmd \
../F2837xD_Headers_nonBIOS_cpu1.cmd 

CLA_SRCS += \
../CLA_TASKs.cla 

LIB_SRCS += \
../2837x_c1bootROM_CLADataROMSymbols_fpu32.lib \
../cla1_math_library_datarom_fpu32.lib 

ASM_SRCS += \
../F2837xD_CodeStartBranch.asm \
../F2837xD_usDelay.asm 

C_SRCS += \
../CLA_config.c \
../F2837xD_Adc.c \
../F2837xD_CpuTimers.c \
../F2837xD_DefaultISR.c \
../F2837xD_EPwm.c \
../F2837xD_GlobalVariableDefs.c \
../F2837xD_Gpio.c \
../F2837xD_PieCtrl.c \
../F2837xD_PieVect.c \
../F2837xD_SysCtrl.c \
../main.c \
../peripherals_setup.c \
../sogi.c 

CLA_DEPS += \
./CLA_TASKs.d 

C_DEPS += \
./CLA_config.d \
./F2837xD_Adc.d \
./F2837xD_CpuTimers.d \
./F2837xD_DefaultISR.d \
./F2837xD_EPwm.d \
./F2837xD_GlobalVariableDefs.d \
./F2837xD_Gpio.d \
./F2837xD_PieCtrl.d \
./F2837xD_PieVect.d \
./F2837xD_SysCtrl.d \
./main.d \
./peripherals_setup.d \
./sogi.d 

OBJS += \
./CLA_TASKs.obj \
./CLA_config.obj \
./F2837xD_Adc.obj \
./F2837xD_CodeStartBranch.obj \
./F2837xD_CpuTimers.obj \
./F2837xD_DefaultISR.obj \
./F2837xD_EPwm.obj \
./F2837xD_GlobalVariableDefs.obj \
./F2837xD_Gpio.obj \
./F2837xD_PieCtrl.obj \
./F2837xD_PieVect.obj \
./F2837xD_SysCtrl.obj \
./F2837xD_usDelay.obj \
./main.obj \
./peripherals_setup.obj \
./sogi.obj 

ASM_DEPS += \
./F2837xD_CodeStartBranch.d \
./F2837xD_usDelay.d 

OBJS__QUOTED += \
"CLA_TASKs.obj" \
"CLA_config.obj" \
"F2837xD_Adc.obj" \
"F2837xD_CodeStartBranch.obj" \
"F2837xD_CpuTimers.obj" \
"F2837xD_DefaultISR.obj" \
"F2837xD_EPwm.obj" \
"F2837xD_GlobalVariableDefs.obj" \
"F2837xD_Gpio.obj" \
"F2837xD_PieCtrl.obj" \
"F2837xD_PieVect.obj" \
"F2837xD_SysCtrl.obj" \
"F2837xD_usDelay.obj" \
"main.obj" \
"peripherals_setup.obj" \
"sogi.obj" 

C_DEPS__QUOTED += \
"CLA_config.d" \
"F2837xD_Adc.d" \
"F2837xD_CpuTimers.d" \
"F2837xD_DefaultISR.d" \
"F2837xD_EPwm.d" \
"F2837xD_GlobalVariableDefs.d" \
"F2837xD_Gpio.d" \
"F2837xD_PieCtrl.d" \
"F2837xD_PieVect.d" \
"F2837xD_SysCtrl.d" \
"main.d" \
"peripherals_setup.d" \
"sogi.d" 

CLA_DEPS__QUOTED += \
"CLA_TASKs.d" 

ASM_DEPS__QUOTED += \
"F2837xD_CodeStartBranch.d" \
"F2837xD_usDelay.d" 

C_SRCS__QUOTED += \
"../CLA_config.c" \
"../F2837xD_Adc.c" \
"../F2837xD_CpuTimers.c" \
"../F2837xD_DefaultISR.c" \
"../F2837xD_EPwm.c" \
"../F2837xD_GlobalVariableDefs.c" \
"../F2837xD_Gpio.c" \
"../F2837xD_PieCtrl.c" \
"../F2837xD_PieVect.c" \
"../F2837xD_SysCtrl.c" \
"../peripherals_setup.c" \
"../sogi.c" 

ASM_SRCS__QUOTED += \
"../F2837xD_CodeStartBranch.asm" \
"../F2837xD_usDelay.asm" 


