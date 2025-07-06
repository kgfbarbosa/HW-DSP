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


/*
 * GPIO34 -> red
 * GPIO31 -> blue
*/
