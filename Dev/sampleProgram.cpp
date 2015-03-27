//sample prgram for testing libraries
#include <lpc214x.h>
#ifndef SAMPLE
	#define SAMPLE
void sampleProgram(void)
{
	//test code 
	PINSEL0=0;
	
	const int led=5;
	IODIR0=(1<<led);
	//toggle led and delay
	IOSET0=(1<<led);
	for(int i=1000000;i>0;i--);
	IOCLR0=(1<<led);
	for(int i=1000000;i>0;i--);
}

#endif