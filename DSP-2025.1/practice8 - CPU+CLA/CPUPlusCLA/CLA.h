/*
 * CLA.h
 *
 *  Created on: Aug 2, 2025
 *      Author: klysm
 */

#ifndef CLA_H_
#define CLA_H_

#include "F2837xD_CLA_defines.h"
#include "CLAMath.h"
#include "F28x_Project.h"
#include "sogi.h"

// Shared variables
extern volatile SPLL_SOGI cla1_pll;
extern volatile float vrede_CLA;
extern volatile float phase_CLA;
extern volatile float ampl_CLA;
extern volatile uint32_t count_task;

// Task's
interrupt void CLA1Task1(); // Task call
interrupt void CLA1Task2();
interrupt void CLA1Task3();
interrupt void CLA1Task4();
interrupt void CLA1Task5();
interrupt void CLA1Task6();
interrupt void CLA1Task7();
interrupt void CLA1Task8();

#endif /* CLA_H_ */
