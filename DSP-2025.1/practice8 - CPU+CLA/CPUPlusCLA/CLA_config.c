/*
 * CLA_config.c
 *
 *  Created on: Aug 2, 2025
 *      Author: klysm
 */

#include "CLA_Config.h"



void CLA1_ConfigCLAMemory(void){
    extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
    EALLOW;
#ifdef _FLASH
    // Copy over code from FLASH to RAM
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
           (uint32_t)&Cla1funcsLoadSize);
#endif //_FLASH

    // Initialize and wait for CLA1ToCPUMsgRAM
    MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};
    // Initialize and wait for CPUToCLA1MsgRAM
    MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
    while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};
    // Select LS5RAM to be the memory space for the CLA (1) or CPU (0)
    // First configure the CLA to be the master for LS5 and then set the space to be
    // a program block (1)
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1;
    // Select LS0RAM and LS1RAM to be the memory space for the CLA (1)
    // First configure the CLA to be the master for LS0/LS1 and then set the space to
    // be a data block (0)
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;
    EDIS;
};



void CLA1_InitCpu1Cla1(void){
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.CLA1 = 1;
    CpuSysRegs.PCLKCR0.bit.DMA = 1;
    Cla1Regs.MVECT1 = (uint16_t)(&CLA1Task1);
    Cla1Regs.MVECT2 = (uint16_t)(&CLA1Task2);
    Cla1Regs.MVECT3 = (uint16_t)(&CLA1Task3);
    Cla1Regs.MVECT4 = (uint16_t)(&CLA1Task4);
    Cla1Regs.MVECT5 = (uint16_t)(&CLA1Task5);
    Cla1Regs.MVECT6 = (uint16_t)(&CLA1Task6);
    Cla1Regs.MVECT7 = (uint16_t)(&CLA1Task7);
    Cla1Regs.MVECT8 = (uint16_t)(&CLA1Task8);

    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all = M_INT1;             // Enable the respective tasks

    // Configure the vectors for the end-of-task interrupt for all 8 tasks
    PieVectTable.CLA1_1_INT = &CLA1_isr1;
    PieVectTable.CLA1_2_INT = &CLA1_isr2;
    PieVectTable.CLA1_3_INT = &CLA1_isr3;
    PieVectTable.CLA1_4_INT = &CLA1_isr4;
    PieVectTable.CLA1_5_INT = &CLA1_isr5;
    PieVectTable.CLA1_6_INT = &CLA1_isr6;
    PieVectTable.CLA1_7_INT = &CLA1_isr7;
    PieVectTable.CLA1_8_INT = &CLA1_isr8;

    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = 1;
    DmaClaSrcSelRegs.CLA1TASKSRCSELLOCK.bit.CLA1TASKSRCSEL1 = 0; // Write a 1 to
       // lock (cannot be cleared once set)
    DmaClaSrcSelRegs.CLA1TASKSRCSELLOCK.bit.CLA1TASKSRCSEL2 = 0; // Write a 1 to
       // lock (cannot be cleared once set)
    EDIS;



};
