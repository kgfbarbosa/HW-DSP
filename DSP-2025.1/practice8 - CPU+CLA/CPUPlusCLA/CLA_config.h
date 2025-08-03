/*
 * CLA_config.h
 *
 *  Created on: Aug 2, 2025
 *      Author: klysm
 *      project based in waner's project
 */

#ifndef CLA_CONFIG_H_
#define CLA_CONFIG_H_

#include "CLA.h"
#include "F28x_Project.h"

void CLA1_ConfigCLAMemory(void);
void CLA1_InitCpu1Cla1(void);

interrupt void CLA1_isr1(void);
interrupt void CLA1_isr2(void);
interrupt void CLA1_isr3(void);
interrupt void CLA1_isr4(void);
interrupt void CLA1_isr5(void);
interrupt void CLA1_isr6(void);
interrupt void CLA1_isr7(void);
interrupt void CLA1_isr8(void);


#endif /* CLA_CONFIG_H_ */
