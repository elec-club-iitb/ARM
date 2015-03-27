#include <lpc214x.h>
#include <math.h>
//sample library development
#include "pll.h"
pll clock(12000000,5,1);
#include "uart.h"
#include "spi.h"
#include "delay.h"
#include "pin.h"
#include "ILI9225.h"
#include <stdio.h>
#include <string.h>

int main()
{
	uart0 serial(clock.getPeripheralClock(),57600);
	#define D(x) serial.printString((char*)(x)); serial.write(0x0d);
	D("serial object created");
	pin rst(124),rs(8),cs(7),led(9);	D("LCD pins initialised");
	spi1 s(clock.getPeripheralClock(),16); 	D("SPI1 module started");
	ILI9225 lcd(&s,rst,rs,cs,led);			 D("LCD object created");
			delay wait(clock.getCpuClock());	D("wait object created");
	 
		lcd.begin(clock.getCpuClock());			D("lcd begin routine done ");
		lcd.clear();													D("LCD cleared");
	unsigned int i=50;
	char str[]="Hello Universe";
	int p=1;
	lcd.setFont(Terminal6x8);								D("lcd font Set");
	lcd.setCursorLimits(50,150,50,51,4);
	char data;
	while (1)
	{
			data=serial.read();
			serial.write(data);
			lcd.drawText(&data,COLOR_GOLD);
			//inefficient text drawing routine !!!
			
		
	}
} 

