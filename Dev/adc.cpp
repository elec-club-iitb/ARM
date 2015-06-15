//adc library
#include "adc.h"
adc0Class::adc0Class()
{
	
}
int adc0Class::read(int pin,int clockDivide, int resolution)
{
	AD0CR=(1<<pin)|((clockDivide-1)<<8)|(0<<16)/*disable burst*/|
					((10-resolution)<<17)|(1<<21)/*power up adc*/|(1<<24)/*start conversion*/;
	//wait while done bit is set 
	while((AD0GDR&(1<<31)) == 0);
	int data= (AD0DR2>>6)&0x3FF;
	return data;
}

