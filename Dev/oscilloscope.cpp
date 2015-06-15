#include "oscilloscope.h"
#include <stdio.h>
#include "FFT.h"
/*all extern variables in header file*/
/**
 * ADC related variables
 */
const int samples = 256;
int AD0_raw[samples];
int AD1_raw[samples];
float AD0_val[samples];
float AD1_val[samples];
int indexADC;
bool isADC_Buffered;
/**
 * DAC related variables
 */
const int DAC_Period = 256;
int indexDAC;
int DAC_raw[DAC_Period];
 
//assigned lower priority to it
__irq void Timer0_Interrupt(void)
{
	//check if DAC interrupt
	
	//readLastConversion
	AD0_raw[indexADC] = (AD0DR2>>6)& 0x3FF;
	AD1_raw[indexADC] = (AD1DR2>>6)& 0x3FF;
	indexADC++;
	//start ADC conversion from ADCGSR , start both simultaneous
	//ADGSR = (1<<24); //start convertion for ADC
	
	AD0CR=(1<<2)/*channel 2*/| (5<<8)/*clock divide by 11+1*/|(1<<24)/*start conversion*/|(1<<21)/*enable ADC*/;
	AD1CR=(1<<2)/*channel 2*/| (5<<8)/*clock divide by 11+1*/|(1<<24)/*start conversion*/|(1<<21)/*enable ADC*/;
	//while((AD0GDR&(1<<31))==0);		//wait while ADC conversion finishes
	
	
	
	
		if(indexADC>=samples)			// if incremented index reaches given number of samples
		{
			isADC_Buffered=true;		
			indexADC = 0;
			//disable timer0 interrupt
			VICIntEnClr=(1<<4);
		}
	T0IR=0x01;				//mark the completion of interrupt by writing to 	the flag
	VICVectAddr=0x00; // signify completed ISR
}
__irq void Timer1_Interrupt(void)
{
		//lcd.drawText(20,20,"interrupt",COLOR_GREEN);
		DACR = DAC_raw[indexDAC];
		indexDAC++;
		if(indexDAC>=DAC_Period)indexDAC =0;
		T1IR = 0x01;				// mark that corresponnding interrupt is executed
		VICVectAddr= 0x00;	//signify completed ISR
}
void initADC(void)
{
	//enable pins for ADC operation
	PINSEL0 |= (3<<20); // for AD1.2
	PINSEL1|=(1<<26);		//for AD0.2
	
}
void EnableInterruptSampling(void)
{
	VICIntEnable = (1<<4)/*enable timer0 interrupt*/;
	//T0MCR &= ~(1<<0);		/*disable Match 0 interrupt (for adc sampling)*/
}
void EnableInterruptWaveGen(void)
{
	//T1MCR &=~(1<<0) ;  /* disable Match 1 interrupt (for DAC out)*/
	VICIntEnable = (1<<5);/*enable timer1 interrupt*/
}
void initTimer0(void)
{
	T0TCR = (1<<0)/*Enable for counting*/|(1<<1)/*reset counter for now*/;
	T0CTCR = 0x00; // every rising PCLK edge for PC
	T0TC =0;	T0PC =0;		//doing anyways , as it is being already reset//may be removed
	T0PR = 29;				//set it has ( PCLK_freq_MHz-1) for getting TC inc at 1 us
	T0MR0 = 2;				// interrupt every 5 us
	T0MCR = (1<<0)/*Interrupt on match*/|(1<<1)/*Reset on MR0*/;
	//using VIC vector 2 for timer
	VICVectCntl2 = (1<<5)/*enable this interrupt*/|4/*timer0 interrupt*/;
	VICVectAddr2 = unsigned(Timer0_Interrupt);
	T0TCR = (1<<0)/*Enable for counting*/;
	
	
}
void initDACout(void)
{

	indexDAC = 0;			// initialise DAC index to 0
	//Enable DAC out pin 
	PINSEL1 |= 0x00080000; // select pin for DAC
	//Enable buffer as funtion with period
	/**
	 *Period : Number of raw samples to repeatedly output
	 *Buffer : LUT ( look up table),stores raw samples to output
	 */
	 
	 for(int i=0;i<DAC_Period;i++)
	 {
			DAC_raw[i] = 500*sin(i*0.1)+500;
			DAC_raw[i] = DAC_raw[i]<<6;		// make it ready to write directly ot DACR register;
	 }
	 
	 
	//Enable Timer for interrupt operation
	T1TCR = (1<<0)|(1<<1);
	T1CTCR = 0x00;
	T1TC = 0; T1PC = 0;
	T1PR = 59;
	T0MR0 = 1; 	//interrupt every 1 us
	T0MCR = (1<<0)/*interrupt on match*/|(1<<1)/*reset on MR0)*/;
	VICVectCntl0 = (1<<5)|5;
	VICVectAddr0 = unsigned(Timer1_Interrupt);
	T1TCR = (1<<0)/*Enable for counting*/;
	//EnableInterruptWaveGen(); /*do later after initialising other routines*/
}
void disableTimer0(void)
{
	T0TCR = 0x2;
}
void disableTimer1(void)
{
	T1TCR = 0x2;
}
void oscilloscope(void)
{
	//init  settings
	indexADC = 0;
	isADC_Buffered = false;
	initADC();
	initDACout();
	initTimer0();
	EnableInterruptSampling();	
	EnableInterruptWaveGen();
	while(1)	
	{
		//lcd.drawText("1",COLOR_BLUE);
		if(isADC_Buffered)
		{
			isADC_Buffered = false;
			// disable Timer0
			disableTimer0();
			//display both ADC graph
			displayGraph(AD0_raw,samples,COLOR_GREEN);
			displayGraph(AD1_raw,samples,COLOR_INDIGO,false);
			displayXY_Plot(AD0_raw,AD1_raw,ILI9225_LCD_WIDTH,COLOR_GREEN,false);
			displayFFT_Plot(AD0_raw,samples,COLOR_RED,false);
			displayFFT_Plot(AD1_raw,samples,COLOR_BLUE,false);
			long avg = 0;
			for(int i=0;i <100 ;i++)avg+=AD0_raw[i];
			avg/=100;
			char buf[20];
			lcd.setOrientation(1);
			sprintf(buf,"Vmean = %d",avg);
			lcd.drawText(0,0,buf,COLOR_WHITE);
			lcd.drawText(20,0,"CH0", COLOR_GREEN);
			//enable timer0 again
			initTimer0();
			EnableInterruptSampling();
		}
		else
		{
			//do nothing
		}
			
	}
	
}


void displayGraph(int * graphData,int len,int color,bool isBackground)
{
	//scale graphdata accordingly
	//display only first LCD_HEIGHT data samples
	float factor = (ILI9225_LCD_WIDTH)/1024.0;
	for ( int i=0; i<len; i++)
	{
			//using  temporary itself to scale and store
			graphData[i] = factor * graphData[i];
	}
	// set window
	if(isBackground)
	{
		lcd.setOrientation(0);
		lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
		for(int x=0;x<ILI9225_LCD_HEIGHT;x++)
		for(int y=0;y<ILI9225_LCD_WIDTH;y++)
		if(x%20==0||y%20==0)lcd._writeData(COLOR_DARKGREEN);
		else lcd._writeData(COLOR_BLACK);
	}
	
	//draw lines for data plot
	
	for(int i = 1;i<ILI9225_LCD_HEIGHT;i++)
	{
		lcd.drawLine(graphData[i-1],i-1,graphData[i],i,color);
		
	}
	
}

void displayXY_Plot(int * graphData1,int* graphData2,int len,int color, bool isBackground)
{
	//scale graphdata accordingly
	//display only first LCD_HEIGHT data samples
	float factor = (ILI9225_LCD_WIDTH)/1024.0;
	for ( int i=0; i<len; i++)
	{
			//using  temporary itself to scale and store
			graphData1[i] = factor * graphData1[i];
			graphData2[i] = factor * graphData2[i];
	}
	// set window
	if(isBackground)
	{
		lcd.setOrientation(0);
		lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
		for(int x=0;x<ILI9225_LCD_HEIGHT;x++)
		for(int y=0;y<ILI9225_LCD_WIDTH;y++)
		if(x%20==0||y%20==0)lcd._writeData(COLOR_DARKGREEN);
		else lcd._writeData(COLOR_BLACK);
	}
	for(int i = 1;i<len;i++)
	{
		lcd.drawLine(graphData1[i-1],graphData2[i-1],graphData1[i],graphData2[i],color);
		
	}
	
}

void displayFFT_Plot(int* graphData, int len, int color, bool isBackground)
{
	complex fftBins[256];
	
	for(int i=0;i<len;i++){
	fftBins[i].Re = graphData[i];
	fftBins[i].Im = 0;
	}
	fft(fftBins,256,1);
	for(int i=0;i<len;i++)fftBins[i].Re = fftBins[i].magnitude();
	float max=0;
	for(int i=5;i<250;i++)	if(fftBins[i].Re>max)max=fftBins[i].Re;
	for(int i=0;i<256;i++)	fftBins[i].Re*=ILI9225_LCD_WIDTH/max;
	if(isBackground)
	{
		lcd.setOrientation(0);
		lcd._setWindow(0,0,ILI9225_LCD_WIDTH,ILI9225_LCD_HEIGHT);
		for(int x=0;x<ILI9225_LCD_HEIGHT;x++)
		for(int y=0;y<ILI9225_LCD_WIDTH;y++)
		if(x%20==0||y%20==0)lcd._writeData(COLOR_DARKGREEN);
		else lcd._writeData(COLOR_BLACK);
	}
	for(int i=1; i<len;i++){
						lcd.drawLine(fftBins[i-1].Re,(i-1),
											fftBins[i].Re,i,color);
				}
}
