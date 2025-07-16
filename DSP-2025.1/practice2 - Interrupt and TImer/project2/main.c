#include "peripherals_setup.h"

/**
 * main.c *
 *  Created on: Jun 25, 2025
 *      Author: klysm
 */

uint32_t count = 0;         // Initialize count variable

interrupt void isr_timer1(void); // Interrupt function

int main(void)
{
    InitSysCtrl();          // Initialize System Resources

    DINT;                   // Disable interrupts

    InitPieCtrl();          // Initialize the PIE control registers to a
                            //      known state.
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // Clear all CPU interrupt flags

    InitPieVectTable();     // Initialize the PIE vector table


    // Interrupts

    EALLOW; //  Enables access to protected registers

    PieVectTable.TIMER1_INT = &isr_timer1;
    //PieCtrlRegs.PIEIER1.bit.INTx7 = 1; // Enables INTx7

    EDIS; //  Disables access to protected registers

    IER |= M_INT13; // Enables column Timer1


    // Timer0 Configuration

    InitCpuTimers();        // Initialize CPU Timers

    ConfigCpuTimer(&CpuTimer1, 200, 1000000);

    CpuTimer1Regs.TCR.all = 0x4000; // Enables Timer0 interrupt


    // GPIO setup

    Setup_GPIO();           // Custom function to configure GPIO pins as outputs

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
    }
}

interrupt void isr_timer1(void){
        // Toggle GPIO31;
        // If GPIO31 is 0, it becomes 1; if it's 1, it becomes 0
    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;

    CpuTimer1Regs.TCR.bit.TIF = 1;
}
