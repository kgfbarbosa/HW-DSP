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
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;                  //habilitar clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm10Regs.TBPRD = 5000;                         // (up/down) period 10Khz Clock/4/fpwm LAB PWM

    //Largura do pulso 50%
    EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD >> 1;

    EPwm10Regs.TBPHS.bit.TBPHS = 0;                  // Phase is 0
    EPwm10Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;
    EPwm10Regs.TBCTR = 0x0000;                       // Clear counter

    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;  // Count up/down
    EPwm10Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // Disable phase loading

    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;        // Clock ratio to SYSCLKOUT
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;     // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm10Regs.AQCTLA.bit.PRD = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.ZRO = AQ_NO_ACTION;
    EPwm10Regs.AQCTLA.bit.CAU = AQ_CLEAR;            // set actions for EPWM10A
    EPwm10Regs.AQCTLA.bit.CAD = AQ_SET;

    //Trigger ADC
    EPwm10Regs.ETSEL.bit.SOCAEN = 1;                 // Enable SOC on A group
    EPwm10Regs.ETSEL.bit.SOCASEL = ET_CTR_PRDZERO;   // Dispara ADC no topo
    EPwm10Regs.ETPS.bit.SOCAPRD = ET_1ST;            // Trigger on every event

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

void Setup_ADC(void){
    Uint16 acqps;

    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit/RESOLUTION)
        acqps = 14;
    else
        acpds = 63;

    EALLOW;
    CpuSysRefs.PCLKCR13.bit.ADC_A = 1;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

}
