//###########################################################################
//
// FILE:	DSP2833x_PieCtrl.c
//
// TITLE:	DSP2833x Device PIE Control Register Initialization Functions.
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V142 $
// $Release Date: November  1, 2016 $
// $Copyright: Copyright (C) 2007-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// InitPieCtrl - This function initializes the PIE control registers to a known
// state.
//
void 
InitPieCtrl(void)
{
    //
    // Disable Interrupts at the CPU level
    //
    DINT;
    
    //
    // Disable the PIE
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

    //
    // Clear all PIEIER registers
    //
    PieCtrlRegs.PIEIER1.all = 0;
    PieCtrlRegs.PIEIER2.all = 0;
    PieCtrlRegs.PIEIER3.all = 0;	
    PieCtrlRegs.PIEIER4.all = 0;
    PieCtrlRegs.PIEIER5.all = 0;
    PieCtrlRegs.PIEIER6.all = 0;
    PieCtrlRegs.PIEIER7.all = 0;
    PieCtrlRegs.PIEIER8.all = 0;
    PieCtrlRegs.PIEIER9.all = 0;
    PieCtrlRegs.PIEIER10.all = 0;
    PieCtrlRegs.PIEIER11.all = 0;
    PieCtrlRegs.PIEIER12.all = 0;

    //
    // Clear all PIEIFR registers
    //
    PieCtrlRegs.PIEIFR1.all = 0;
    PieCtrlRegs.PIEIFR2.all = 0;
    PieCtrlRegs.PIEIFR3.all = 0;	
    PieCtrlRegs.PIEIFR4.all = 0;
    PieCtrlRegs.PIEIFR5.all = 0;
    PieCtrlRegs.PIEIFR6.all = 0;
    PieCtrlRegs.PIEIFR7.all = 0;
    PieCtrlRegs.PIEIFR8.all = 0;
    PieCtrlRegs.PIEIFR9.all = 0;
    PieCtrlRegs.PIEIFR10.all = 0;
    PieCtrlRegs.PIEIFR11.all = 0;
    PieCtrlRegs.PIEIFR12.all = 0;
}	

//
// EnableInterrupts - This function enables the PIE module and CPU interrupts
//
void 
EnableInterrupts()
{
    //
    // Enable the PIE
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

    //
	// Enables PIE to drive a pulse into the CPU 
    //
	PieCtrlRegs.PIEACK.all = 0xFFFF;  

    //
	// Enable Interrupts at the CPU level 
    //
    // EINT;


    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//��ʱ��0�жϡ�
	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;//ePWM1�ж�
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;//ECAP1
	PieCtrlRegs.PIEIER4.bit.INTx2 = 1;//ECAP2
	PieCtrlRegs.PIEIER4.bit.INTx3 = 1;//ECAP3

	PieCtrlRegs.PIEIER8.bit.INTx5 = 1;//SCIC RX Interrupt
	PieCtrlRegs.PIEIER8.bit.INTx6 = 1;//SCIC TX Interrupt
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;//SCIB RX interrupt
//	PieCtrlRegs.PIEIER9.bit.INTx4 = 1;//SCIB TX interrupt

//	EPwm1Regs.ETSEL.bit.INTEN =1;

	ScibRegs.SCIFFTX.bit.TXFFINTCLR = 1;
	ScibRegs.SCIFFRX.bit.RXFFINTCLR = 1;

	// Enable Interrupts at the CPU level 
    EINT;
    ERTM;
}

//
// End of file
//

