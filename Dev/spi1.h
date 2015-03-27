#ifndef SPI1_H
	#define SPI1_H
	#include  <lpc214x.h>
/*
Registers : 
SSPCR0 : selscts the serial clock rate, bus type and data size
SSPCR1 : selects the master slave and other modes
SSPDR  : Data register, Writes fill the transmit FIFO.
			and reads empty the receive FIFO
SSPSR : Status Register
SSPCPSR: Clock prescale register
SSPIMSC: interrupt mask set and clear register
SSPRIS : Raw interrupt Status register
SSPMIS : masked interrupt status register
SSPMIS : masked interrupt status register
SSPICR : SSPICR Interrupt Clear Register
*/

class spi1{

		unsigned long clock,clkDiv,dataLength;
	private : 
		void initPins(void);
	public: 
		spi1();
		spi1(unsigned long pclk,int _dataLength=16,int _clkDiv=2);
		void setClockDiv(int factor);
		void setDataLength(int len);
		int rw(int data=0xFFFF);
		void w(int data);
};
#endif