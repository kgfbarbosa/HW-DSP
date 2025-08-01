#include "peripherals_setup.h"
#include "sogi.h"
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
uint32_t count = 0, index = 0;

SPLL_SOGI v_pll;
float vrede = 0;
float vsync = 0;
float phase = 0;
float ampl = 0.5;

float plot1[512], plot2[512];
float *padc1 = &vrede;
float *padc2 = &vsync;


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

    ConfigCpuTimer(&CpuTimer0, 200, 1000000);

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


    // SOGI setup
    SOGI_init(60, 32.5520833E-06, &v_pll);
    SOGI_coeff_update(32.5520833E-06, 376.99112, 0.7, &v_pll);


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

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void isr_adc(void){
    GpioDataRegs.GPADAT.bit.GPIO14 = 1;
    vrede = 0.005*((int)AdcaResultRegs.ADCRESULT0 - 0x7FF);

    v_pll.u[0] = vrede;
    SPLL_SOGI_CALC(&v_pll);

    vsync = v_pll.sin_;

    EPwm7Regs.CMPA.bit.CMPA = (uint16_t) (1627.0 * (1.0 + ampl + __sin(v_pll.theta[1] + phase)));

    EALLOW;
    DacbRegs.DACVALS.bit.DACVALS = (uint16_t) (2047.0 * (1.0 + ampl + __sin(v_pll.theta[1] + phase)));
    EDIS;

    plot1[index] = *padc1;
    plot2[index] = *padc2;
    index = (index == 511) ? 0 : (index + 1);

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;  // Clear INT1 flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GpioDataRegs.GPADAT.bit.GPIO14 = 0;
}
