/*
 * peripherals_setup.c
 *
 *  Created on: Jun 25, 2025
 *      Author: klysm
 */

#include "peripherals_setup.h"

void Setup_GPIO(void){
    EALLOW; //  Enables access to protected registers

    //GPIO34: output
    GpioCtrlRegs.GPBGMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;                 // PUD on
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;                 // Direction set as output
                                                        // only valid for GPIO
    GpioCtrlRegs.GPBCSEL1.bit.GPIO34 = GPIO_MUX_CPU1;   // Chooses CPU1

    //GPIO31: output
    GpioCtrlRegs.GPAGMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 1;                 // PUD on
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;                 // Direction set as output
                                                        // only valid for GPIO
    GpioCtrlRegs.GPACSEL4.bit.GPIO31 = GPIO_MUX_CPU1;   // Chooses CPU1

    EDIS; //  Disables access to protected registers
}

void Setup_DAC(void){
    EALLOW; //  Enables access to protected registers

    // Configure DAC-B control registers
    DacbRegs.DACCTL.all = 0x0001;

    // Set DAC-B output to mid-range
    DacbRegs.DACVALS.all = 0x0800;

    // Enable DAC-B output
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;                 // 0 = disable, 1 = enable

    // DAC-B lock control register
    DacbRegs.DACLOCK.all = 0x0000;

    EDIS; //  Disables access to protected registers
}


void Setup_ePWM10(void){
    EALLOW; // Enables access to protected registers

    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;                  // Enables clock
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;               // Enables table clock synchronization
    EPwm10Regs.TBPRD = 5000;                            // period (up/down) 10Khz Clock/4/fpwm LAB PWM

    // Pulse Width 50 %
}
