//spi library header file
#ifndef SPI_H
	#define SPI_H
	#include <lpc214x.h>
	#include "pin.h"
/*
		SCK  -> P0.4
		MISO -> P0.5
		MOSI -> P0.6
		SSEL -> P0.7
*/

//INITIALISATION
//set clock
//set control
//set IO
//set datalength
//READ/WRITE
//	
		
class spi0 {
		
		 unsigned long clock/*clock of spi bus*/,clkDiv,dataLength;
			unsigned long pclk;
		pin _chipSelect;
	private : 
		void initPins(void);
	public  : 
			spi0();
			spi0(unsigned long pclk,int dataLength=8,int clkDiv=8);
	
			void enableCS();
			void disableCS();
			void w(int data);
			void setClockDiv(int factor);
			void setDataLength(int len);
			int rw(int data=0xFFFF);
};
#endif