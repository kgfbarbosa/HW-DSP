#include "peripherals_setup.h"
#include "math.h"

/**
 * main.c *
 *  Created on: 7/14/2025
 *      Author: klysm
 */

// Interrupt functions

interrupt void isr_timer0(void);            // Interrupt timer0 function
interrupt void isr_adc(void);               // Interrupt ADC function


// Variables

uint32_t count = 0;                         // Initialize count variable
uint16_t ADCIndex = 0, sinusoidalIndex = 0; // Initialize ADC index and sinusoidal index
uint16_t sintable[400], costable[400];      // Initialize sine table and cosine table
uint16_t sinOffset = 0, cosOffset = 0;      // Initialize offset 1 and 2
uint16_t ADC1 = 0, ADC2 = 0, plot[400];     // Initialize ADC 1 and 2 and plot variables
uint16_t *ADC = &ADC1;                      // Initialize ADC pointer


int main(void)
{
    InitSysCtrl();          // Initialize System Resources

    DINT;                   // Disable interrupts

    InitPieCtrl();          // Initialize the PIE control registers to a
                            //      known state.
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // Clear all CPU interrupt flags

    InitPieVectTable();     // Initialize the PIE vector table


    // Interrupts setup

    EALLOW; //  Enables access to protected registers

    PieVectTable.TIMER0_INT = &isr_timer0;  // Timer0 treatment
    PieVectTable.ADCA1_INT = &isr_adc;      // ADC treatment

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      // Enables INTx7 (Timer0 column)
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;      // Enables INTx1 (ADC column)

    EDIS;   //  Disables access to protected registers

    IER |= M_INT1; // Enables column 1


    // Modules setup
    // Timer0 setup

    InitCpuTimers();        // Initialize CPU Timers

    ConfigCpuTimer(&CpuTimer0, 200, 50);

    CpuTimer0Regs.TCR.all = 0x4000; // Enables Timer0 interrupt


    // GPIO setup

    Setup_GPIO();           // Custom function to configure GPIO pins as outputs


    // DAC setup

    Setup_DAC();


    // PWM setup

    Setup_ePWM1();
    Setup_ePWM2();
    Setup_ePWM3();
    Setup_ePWM7();
    Setup_ePWM8();
    Setup_ePWM10();


   // ADC setup

    Setup_ADC();


    // Sinusoidal tables setup
    for (sinusoidalIndex = 0; sinusoidalIndex < 400; sinusoidalIndex++){
        sintable[sinusoidalIndex] = (uint16_t)(2500.0*(1.0 + sin(6.28318531/400.*(float)sinusoidalIndex)));
        costable[sinusoidalIndex] = (uint16_t)(2500.0*(1.0 + cos(6.28318531/400.*(float)sinusoidalIndex)));
    }
    sinusoidalIndex = 0;


    EINT;                   // Enable global interrupt INTM
    ERTM;                   // Enable global real-time debug interrupt DBGM

    // Initialize both GPIO pins to low logic (0)
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;

    while(1){
        // Delay loop (software delay for timing)
        for (count = 0; count < 0x005FFFFF; count++);

        // Toggle GPIO34;
        // If GPIO34 is 0, it becomes 1; if it's 1, it becomes 0
        GpioDataRegs.GPBDAT.bit.GPIO34 ^= 1;

        // Another delay loop, with different length to create de-synchronization
      //  for (count = 0; count < 0x00AFFFFF; count++);

        // Toggle GPIO31;
        // If GPIO31 is 0, it becomes 1; if it's 1, it becomes 0
      //  GpioDataRegs.GPADAT.bit.GPIO31 ^= 1;
    }
}

interrupt void isr_timer0(void){
    //GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

    sinusoidalIndex = (sinusoidalIndex == 399) ? 0 : (sinusoidalIndex + 1);

    DacbRegs.DACVALS.all = sinOffset + sintable[sinusoidalIndex]/2; // Sine table output
    DacbRegs.DACVALS.all = cosOffset + costable[sinusoidalIndex]/2; // Cosine table output

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void isr_adc(void){
    ADC1 = AdcaResultRegs.ADCRESULT0;
    ADC2 = AdcaResultRegs.ADCRESULT1;

    ADCIndex = (ADCIndex == 399) ? 0 : (ADCIndex + 1);
    EPwm7Regs.CMPA.bit.CMPA = sintable[sinusoidalIndex];
    EPwm8Regs.CMPA.bit.CMPA = sintable[sinusoidalIndex];

    plot[ADCIndex] = *ADC;

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  // Clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
