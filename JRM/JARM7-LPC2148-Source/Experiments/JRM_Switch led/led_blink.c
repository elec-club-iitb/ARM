#include <LPC214X.H>

//#include "Utility.h"

int wait(unsigned int w)
{
	unsigned int a,b;

	for(a=0;a<w;a++)
		for(b=0;b<200;b++);
}


int main (void)
{
	
	unsigned long int get;
	
	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;
	PINSEL2 = 0x00000000;
//	PINSEL2 |= 0x00000030;
//	DelayProc(0.2 * CCLOCK);
  
	IODIR0 = 0xFFFF00FF;
	
	IOSET0 = 0XFFFFFFFF;
	wait(20000);					
	IOCLR0 = 0xFFFFFFFF;

	IODIR1 = 0X00FFFFFF;
	IOCLR1 = 0XFFFFFFFF;


	
	while (1)
		{
			IOSET0 = IOPIN0 >> 8;
			wait(20000);
			IOCLR0 = 0XFFFFFFFF;			
		}
}
