/**
 * main.c
 */
#include "DSP2833x_Device.h"     // DSP280x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP280x Examples Include File
#include <stdio.h>
#include <string.h>


#define UART_PRINTF

#ifdef UART_PRINTF
    int fputc(int _c, register FILE *_fp);
    int fputs(const char * _ptr, register FILE *_fp);
#endif

#ifdef UART_PRINTF
    int fputc(int _c, FILE *_fp)
    {
        while(ScibRegs.SCIFFTX.bit.TXFFST != 0){
        }
        ScibRegs.SCITXBUF = (unsigned char) _c;
        return ((unsigned char) _c);
    }
    int fputs(const char * _ptr, register FILE *_fp){
        unsigned int i, len;
        len = strlen(_ptr);
        for(i = 0; i < len; ++i){
            while(ScibRegs.SCIFFTX.bit.TXFFST !=0){
            }
            ScibRegs.SCITXBUF = (unsigned int) _ptr[i];
        }
        return len;
    }
#endif




void scib_loopback_init(void)
{
 	ScibRegs.SCICCR.all 			= 0x0007;   // 1 stop bit,  No loopback
	ScibRegs.SCICTL1.all 			= 0x0003;  // enable TX, RX, internal SCICLK,
	ScibRegs.SCICTL2.all 			= 0x0003;
	ScibRegs.SCICTL2.bit.TXINTENA 	= 1;
	ScibRegs.SCICTL2.bit.RXBKINTENA = 1;
	ScibRegs.SCIHBAUD    			= 0x00;//0x00;-------------------------0x01
	ScibRegs.SCILBAUD    			= 0x1f;//0x17:115200-------------------0x24:9600 90M
	ScibRegs.SCICCR.bit.LOOPBKENA 	= 0; // enable loop back
	ScibRegs.SCICTL1.all 			= 0x0023;     // Relinquish SCI from Reset
}

void scib_fifo_init(void)
{
  ScibRegs.SCIFFTX.bit.TXFIFOXRESET	= 0;
  ScibRegs.SCIFFRX.bit.RXFIFORESET	= 0;
  ScibRegs.SCIFFTX.all				= 0xE028;
  ScibRegs.SCIFFTX.bit.TXFFIENA		= 0;

  ScibRegs.SCIFFTX.bit.TXFFINTCLR		= 1;
  ScibRegs.SCIFFRX.all				= 0x2028;

  ScibRegs.SCIFFRX.bit.RXFFIENA		= 1;
  ScibRegs.SCIFFCT.all				= 0x0;
}

void delayCount(int32 count){
    int32 i;
	for(i = 0; i < count; ++i){
		asm("   NOP");
	}
}

void InitInterrupt(void){
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
    IER |= M_INT1;
    IER |= M_INT2;
    IER |= M_INT3;
    IER |= M_INT4;
    IER |= M_INT7;
 	IER |= M_INT8;//SCIc
    IER |= M_INT9;//SCIa//ECAN//scib
    IER |= M_INT13;//timer1
	EnableInterrupts();
}

int main(void)
{
    InitSysCtrl();

    InitSciGpio();

    scib_loopback_init();

    scib_fifo_init();

    InitInterrupt();

	while(1){
    	printf("test\n");
    	printf("-----------------------\r\n");
    	printf("boot loader start\r\n");
        delayCount(100000);
	}
}
