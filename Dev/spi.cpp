//spi library
#include "spi.h"
//Initialise spi pins on  P0.4
spi0::spi0()
{
}
void spi0::initPins(void)
{
	PINSEL0=(PINSEL0&0xFFFF00FF)|0x00001500;	//let manually control CS pin
	pin cs(7);
	_chipSelect=cs;
	//  PINSEL0 = (PINSEL0 & ~(3 << 12)) | (1 << 12); //  MOSI0 SPI0
  //   PINSEL0 = (PINSEL0 & ~(3 << 10)) | (1 << 10); //  MISO0 SPI0
  //   PINSEL0 = (PINSEL0 & ~(3 << 8))  | (1 << 8);  //  SCK0  SPI0
}

//Set constructor 
spi0::spi0(unsigned long _pclk,int _dataLength,int _clkDiv)
{
	pclk=_pclk;
	clock=pclk/_clkDiv;			//save for clock
	dataLength=_dataLength;	
	clkDiv=_clkDiv;
	initPins();		//initialse pins
	setClockDiv(clkDiv);		//initialise clock
	S0SPCR=(0xF00&(dataLength<<8))|(1<<5)|(0<<4)|(0<<3)|(1<<2);	//initialse control register
	S0SPDR=0;
}
void spi0::enableCS()
{
	_chipSelect.low();
}
void spi0::disableCS()
{
	_chipSelect.high();
}
void spi0::setClockDiv(int factor)//8<=factor <=255
{
	disableCS();
	if(factor<8)factor=8; //make sure factor is always greater than 8
	clkDiv=factor&(~0x1);		//save with lsb always 0
	S0SPCCR=clkDiv;		//number of pclk cycles that
	clock=pclk/clkDiv;
										//make up one spiclock cycle
}
void spi0::setDataLength(int len)	//length 8bits to 16 bits
{
	dataLength=len; 	//save a new copy
	S0SPCR= (S0SPCR&(~0xF00))|(len<<8);
}

int spi0::rw(int data)
{
	
	S0SPDR=data;
	while(!(S0SPSR&0x80));
	int dummy =S0SPDR;
	return dummy;
}
void spi0::w(int data)
{	
	S0SPDR=data;
	while(!(S0SPSR&0x80));
}
