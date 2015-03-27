#include <lpc21xx.h>
#include "DELAY.cpp"
//
int main()
{
	const int led=5;//port 0, P0.2
	PINSEL0=0;
	IODIR0=(1<<led);
	while(1){
	
	delay(1000000);
	IO0CLR=1<<led;
	delay(1000000);
	}
}
