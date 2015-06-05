#include <lpc214x.h>
#include <math.h>
#include <stdlib.h>
#include <string>
//sample library development
//created by ajinkya gorad
#include "pll.h"
pll clock(12000000,5,1);
#include "uart.h"
#include "spi.h"
#include "delay.h"
#include "pin.h"
#include "ILI9225.h"
#include <stdio.h>
#include <string.h>
#include "process.h"
#include "adc.h"
#include "dac.h"


uart0 serial(clock.getPeripheralClock(),38400);
pin rst(124),rs(8),cs(7),led(9);
spi1 s(clock.getPeripheralClock(),16);
ILI9225 lcd(&s,rst,rs,cs,led);			
delay wait(clock.getCpuClock());
adc0Class adc0;
dacClass dac;
// input normalised sample
float getFreqComp(float* sample, int size,float freq);
void getDFT(float* sample,float* bin,int size);

void getDFT(float* sample  ,float* bin,int size)
{
		for( int k=0;k<size;k++)
		{
			bin[k] = getFreqComp(sample,size,6.28*k/size);
		}
		float max=-5;
		for(int k=0;k<size;k++)
		{
			if(bin[k]>max)max=bin[k];
		}
		for(int k=0;k<size;k++)
		{
			bin[k]/=max;
		}
}

float getFreqComp(float* sample, int size,float freq)
{
	float real=0,img=0;
	for(int i=0;i<size;i++)
	{
		real+= sample[i]*cos(freq*i);
		img+=  sample[i]*sin(freq*i);
	}
	return sqrt(real*real+img*img);
}
void graph2(void)
{
	float buffer[ILI9225_LCD_HEIGHT];	//create a buffer 
	//float sample[ILI9225_LCD_HEIGHT];
	
	/*initialise buffer*/
	//pin adread(29);	//corresponds to pin A02
	PINSEL1|=(1<<26);
	//adread.input();
	int triggerRising = 40;
	lcd.setFont(Terminal6x8);	
	dac.init();
	dac.write(500);
	//lcd.drawText("Starting",COLOR_BLUE);
	while(1){
	//lcd.drawText("!",COLOR_YELLOWGREEN);
	buffer[0]=(ILI9225_LCD_WIDTH*adc0.read(2,clock.getPeripheralClock()/10000000))/1024;
	int f1 = rand()%10;
	int f2 = rand()%20;
	for(int i=1;i<ILI9225_LCD_HEIGHT;i++)
	{
		//sample[i]=(adc0.read(2,clock.getPeripheralClock()/4500000))/1024.0;
		//buffer[i]=(ILI9225_LCD_WIDTH)*sample[i];	//scale it according to LCD width for displaying
		buffer[i]=(ILI9225_LCD_WIDTH*adc0.read(2,clock.getPeripheralClock()/4500000))/1024.0;
		//dac.write(int(400.0+200*sin(i*0.1)+200*sin(i*0.03)));
		if((buffer[i]>triggerRising)/*if greater thatn trigger*/&&(buffer[i]>buffer[i-1])/*if rising*/)
		{
			//record continuous samples 
			
			for(int i=0;i<ILI9225_LCD_HEIGHT;i++){
					//dac.write(int(400.0+200*sin(i*f1*0.1)+200*sin(i*f2*0.1)));
				//	sample[i]=(adc0.read(2,clock.getPeripheralClock()/4500000))/1024.0;
				//	buffer[i]=(ILI9225_LCD_WIDTH)*sample[i];	//scale it according to LCD width for displaying
						buffer[i]=(ILI9225_LCD_WIDTH*adc0.read(2,clock.getPeripheralClock()/4500000))/1024.0;
					}
			break;		//break out of loop
		}
		else 
		{
			//record normally
		}
	}
	//lcd.drawText("DFT",COLOR_BLUEVIOLET);
	float dft[ILI9225_LCD_HEIGHT];
	getDFT(buffer,dft,ILI9225_LCD_HEIGHT);
	//now buffer has the data to display for signal
	//and dft  has the data to display for spectrum
	// now scale spectrum for display on LCD
	//lcd.drawText("@",COLOR_BLUE);
	for(int i=0;i<ILI9225_LCD_HEIGHT;i++)		dft[i]*=ILI9225_LCD_WIDTH*(1.0-log(dft[i]));
	
	//char str[50];
	
	long mean=0;
	for(int i=0;i<ILI9225_LCD_HEIGHT;i++)		mean+=buffer[i];
	mean/=ILI9225_LCD_HEIGHT;
	
	//sprintf(str,"Mean : %i \n",int(mean));
	//serial.printString(str);
	//setup grid+clear last data on lcd
	lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
	for(int y=0;y<ILI9225_LCD_HEIGHT;y++)
	for(int x=0;x<ILI9225_LCD_WIDTH;x++)
	if(x%20==0||y%20==0)lcd._writeData(COLOR_DARKGREEN);
	else lcd._writeData(COLOR_BLACK);
	
	//lcd.drawText(0,0,str,COLOR_WHITE);	
	
	for(int i=1; i< ILI9225_LCD_HEIGHT;i++){
		
					lcd.drawLine(buffer[i-1],(i-1),buffer[i],i,COLOR_YELLOW);
						lcd.drawLine(dft[i-1],i-1,dft[i],i,COLOR_RED);
				}
		}//end of while loop 
}
void graph(void)
{
		
	for(int y=0;y<ILI9225_LCD_HEIGHT;y++)
	for(int x=0;x<ILI9225_LCD_WIDTH;x++)
	{
			if(abs(sin( (y/40.0)-40.0)-(x/40.0)	)<0.05)
			{
				 lcd.drawPixel(x,y,COLOR_CYAN);
			}
	}
}
	
void draw1(void)
{
	lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
	for(int y=0;y<ILI9225_LCD_HEIGHT;y++)
	for(int x=0;x<ILI9225_LCD_WIDTH;x++)
	//lcd.drawPixel(x,y,20*((x-20)*(y-20)));
	lcd._writeData(20*((x-20)*(y-20)+x));
	
}
void draw2(void)
{
	lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
	for(int y=0;y<ILI9225_LCD_HEIGHT;y++)
	for(int x=0;x<ILI9225_LCD_WIDTH;x++)
	//lcd.drawPixel(x,y,20*(x*x+y*y));
	lcd._writeData(20*(x*x+y*y));
}
int main()
{
	
	#define D(x) serial.printString((char*)(x)); serial.write(0x0d);

	
	lcd.begin(clock.getCpuClock());			
	lcd.clear();												
	D("Initialised");
	
	
	
	
	
	lcd.setFont(Terminal6x8);								D("lcd font Set");
	lcd.setCursorLimits(50,150,50,90,2);
	lcd.drawText("Initialsed",COLOR_BLUE);
	wait.ms(500);
	processor processing;
	processing.add(graph2,"g2");
	processing.add(graph,"g");
	processing.add(draw1,"1");
	processing.add(draw2,"2");
	graph2();
	char data;
	while (1)
	{
			//data=serial.read();
			//serial.write(data);
			char *cmd=serial.getCommand('*');
			D("command Received");
			serial.printString(cmd);
			processing.process(cmd);
			
			//lcd.drawText(&data,COLOR_GOLD);
			
			//inefficient text drawing routine !!!
		
			
		
	}
} 

