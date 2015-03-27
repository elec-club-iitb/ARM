#include "spi1.h"
spi1::spi1(void)
{
}
void spi1::initPins()
{
	PINSEL1=(PINSEL1&0xFFFFFFFF)|0x000002A8;
	
}
spi1::spi1(unsigned long pclk,int _dataLength,int _clkDiv)
{
		clock=pclk/_clkDiv;
		dataLength=_dataLength;
		clkDiv=_clkDiv;
		initPins();		//initialse pins
		setClockDiv(clkDiv);		//initialise clock
		SSPCR0=(0<<7)|(0<<6)|(dataLength-1);		//CPOL, CPHA
		SSPCR1=(1<<1);
		SSPIMSC=0;
		
}

void spi1::setClockDiv(int factor)
{
	clkDiv=factor;		//save 
	SSPCPSR=clkDiv;
}
void spi1::setDataLength(int len)
{																																																																		
	SSPCR0&=~0x0F;
	SSPCR0|=(len-1);
}

int spi1::rw(int data)
{

}
void spi1::w(int data)
{	
	while(!(SSPSR&(1<<1)));
	
	SSPDR=data;
	/*/
while (!(SSPSR & 0x02));

SSPDR = data; // Place data to be sent into SPI data register
while(SSPSR&(1<<4)); // Wait for transfer to complete
*/
}