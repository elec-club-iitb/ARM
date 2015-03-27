//library for delay
#include "delay.h"
// initialise delay object 
delay::delay(unsigned long _fcpu)
{
	fdelay=_fcpu/4.92;//fdelay=fcpu/k ;find k by experiment
}

//delay for x clocks
void delay::clocks(unsigned long clk)
{
	while(clk--);
}
//delay for milliseconds
void delay::ms(unsigned long t)
{
	clocks((fdelay/1000)*t);
}
void delay::us(unsigned long t)
{
	clocks((fdelay/1000000)*t);
}void delay::s(float t)
{
	clocks(fdelay*t);
}
