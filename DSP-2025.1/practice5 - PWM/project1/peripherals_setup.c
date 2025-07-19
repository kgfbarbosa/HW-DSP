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

    // Configure DAC-A and DAC-B control registers
    DacaRegs.DACCTL.all = 0x0001;
    DacbRegs.DACCTL.all = 0x0001;

    // Set DAC-A and DAC-B output to mid-range
    DacaRegs.DACVALS.all = 0x0800;
    DacbRegs.DACVALS.all = 0x0800;

    // Enable DAC-A and DAC-B output
    DacaRegs.DACOUTEN.bit.DACOUTEN = 1;                 // 0 = disable, 1 = enable
    DacbRegs.DACOUTEN.bit.DACOUTEN = 1;                 // 0 = disable, 1 = enable

    // DAC-A and DAC-B lock control register
    DacaRegs.DACLOCK.all = 0x0000;
    DacbRegs.DACLOCK.all = 0x0000;

    EDIS; //  Disables access to protected registers
}


void Setup_ePWM1(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;                // Enable module clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;            // Disable counter clock

    EPwm1Regs.TBPRD = 50000;                         // Period Fosc/2*Fpwm or Fosc/4*Fpwm
    EPwm1Regs.TBPHS.bit.TBPHS = 0;                   // Phase is 0
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTR = 0;                             // Clear counter
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Count up/down
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;         // Prescale
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD >> 1;  // Duty 50%

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;      // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO_PRD;

    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set actions for EPwm1A
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_NO_ACTION;

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;            // Enable counter clock
    EDIS;
}


void Setup_ePWM10(void){
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM10 = 1;           //habilitar clock

    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;

    EPwm10Regs.TBPRD = 5000;                         //periodo (up/down) 10Khz Clock/4/fpwm LAB PWM

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

    // determine minimum acquisition window (in SYSCLKS) based on resolution
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
        acqps = 14;                         // 75ns
    else                                    // resolution is 16-bit
        acqps = 63;                         // 320ns

    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;   // Set pulse one cycle before the result
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;      // Power up the ADC
    DELAY_US(1000);                         // Delay for 1ms to allow ADC timer to power up

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 3;      // ADCINA3 - J3-26
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0x17;

    // SOC = Start of conversion
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 4;      // ADCINA3 - J7-69
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps;  // sample window is 15 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0x17;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0x01;   // end of SOC1 will set INT1 flag (source)
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;        // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      // make sure INT1 flag is cleared
}
