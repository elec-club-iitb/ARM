#include<string.h>
#include <LPC214x.H>
#include "lcd.h"

void RTC_Init(void);		  /* Initialize RTC */
void RTCStart(void);		  /* Start RTC */
void Read_rtc(void);		  // READ from RTC

int main (void) 
{
  	init_lcd();
  	RTC_Init();		/* Initialize RTC */
  	RTCStart();		/* Start RTC */
 
    while(1)
 		Read_rtc();

}


void RTC_Init()
{
  	CCR=0x00;	//Clock Counter Cleared, Clocks Source PCLK, Clock Tick Counter Reset

	/* ((456+1)*32768) + 25024 = 15000000 */
  	PREINT = 0x000001C8; 							//456 is The Integer Part of the Prescaler
  	PREFRAC = 0x000061C0;							//25024 is the Fraction Part of the Prescaler

 	SEC=58;
  	MIN=14;
  	HOUR=18;
  	DOM=02;
	MONTH=01;
	YEAR=2011;
}

void RTCStart( void )
{
    CCR = 0x01; 	 			// clock enable
}

void Read_rtc( void )
{
	char date1[17];
	char time1[17];
	sprintf(date1,"DATE: %.2d-%.2d-%.4d",DOM,MONTH,YEAR);
	sprintf(time1,"TIME: %.2d:%.2d:%.2d  ",HOUR,MIN,SEC);
	// print the saved string
	lcd_putstring(0,date1);
	lcd_putstring(1,time1);

	return;
}
