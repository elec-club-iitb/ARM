#include "dac.h"
dacClass::dacClass()
{
}
void dacClass::init()
{
		PINSEL1 |= 0x00080000	;//select pin for DAC
		//IO0DIR|=(1<<25);			//set P0.25 as output
}

void dacClass::write(int value)
{
		DACR=(value)<<6;
}