//UART library
#include "uart.h"
#include "lpc214x.h"
//
uart0::uart0(unsigned long _pclk,
						unsigned long _baud,
						 unsigned int _dataWidth,
						 unsigned int _stopBits,
						 int parity){
	baud=_baud;
	stopBits=_stopBits;
	dataWidth=_dataWidth;
	pclk=_pclk;
	
	PINSEL0&=0xfffffff00;	//mask out other pins
	PINSEL0|=0x05;	//configure pins for RX and TX
							 int parityEnable=0;
	if(parity==1||parity==2)parityEnable=1;
	if(parity==2)parity=0;
	U0LCR=(0x80)+16*parity+8*(parityEnable)+4*(stopBits-1)+(dataWidth-5);//register info generating  function
	callSetBaud();
	U0LCR = 0x00000003; // DLAB =0				 
							 
	
	
	
	//U0FCR=0x1;			//Enable FIFO's
	
	
	
	//U0TER=0x80;
							 
}			
void uart0::callSetBaud()	//loads U0DL M/L register with required values  for baud rate 
{
	//float baudFactor=pclk/16.0/baud;
	//unsigned int integerFactor=baudFactor;
	//baudFactor-=integerFactor;
	unsigned short f=pclk/(16*baud);
	U0DLL=f&0xFF;
	U0DLM=(f>>8);
}	
void uart0::setBaud(unsigned long _baud)
{
	baud=_baud;		//load with required baud rate
	callSetBaud();
}
void uart0::write(char data)
{
	while (!(U0LSR & 0x20));
	U0THR=data;

	
}
unsigned long uart0::getBaud()
{
	return baud;
}
char uart0::read(void)
{	
	 while(!(U0LSR&0x01));
	return U0RBR;
}

void uart0::printString(char * ch)
{
	while(1)
	{	
		write(*ch);
		ch++;
		if(*ch=='\0')break;
	}
}