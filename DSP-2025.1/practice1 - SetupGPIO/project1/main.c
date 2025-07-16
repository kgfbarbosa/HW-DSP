#include "peripherals_setup.h"

/**
 * main.c
 */

uint32_t count = 0;         // Initialize count variable

int main(void)
{
    InitSysCtrl();          // Initialize System Resources

    DINT;                   // Disable interrupts

    InitPieCtrl();          // Initialize the PIE control registers to a
                            //      known state.
    IER = 0x0000;           // Disable CPU interrupts
    IFR = 0x0000;           // Clear all CPU interrupt flags

    InitPieVectTable();     // Initialize the PIE vector table


    // GPIO setup

    Setup_GPIO();           // Custom function to configure GPIO pins as outputs

    EINT;                   // Enable global interrupt INTM
    ERTM;                   // Enable global real-time debug interrupt DBGM

    // Initialize both GPIO pins to low logic (0)
    GpioDataRegs.GPBDAT.bit.GPIO34 = 0;
    GpioDataRegs.GPADAT.bit.GPIO31 = 0;

    while(1){
        // Delay loop (software delay for timing)
        for (count = 0; count < 0x005FFFFF; count++);

        // Toggle GPIO34;
        // If GPIO34 is 0, it becomes 1; if it's 1, it becomes 0
        GpioDataRegs.GPBDAT.bit.GPIO34 ^= 1;

        // Another delay loop, with different length to create de-synchronization
        for (count = 0; count < 0x00AFFFFF; count++);

        // Toggle GPIO31;
        // If GPIO31 is 0, it becomes 1; if it's 1, it becomes 0
        GpioDataRegs.GPADAT.bit.GPIO31 ^= 1;
    }
}
