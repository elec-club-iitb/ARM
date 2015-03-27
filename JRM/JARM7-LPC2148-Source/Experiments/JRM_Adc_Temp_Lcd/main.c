#include <stdio.h>
#include <LPC214x.H>                       /* LPC214x definitions */
#include "lcd.h"
#include "adc.h"

/**
**************************************************************************

****1111
  Function Name : wait()

  Description :This function suspends the tasks for specified ticks.	

  Input :  ticks:no of ticks in multiple of 1 usec
            task: task to be suspended

  Output : void

  Note :
*******************************************************************************
*/

void wait(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}
/**
********************************************************************************************
	Function Name :	process_temp_sensor_adc()

	Description :
	
	Input :	Void

	Output : Void

	Note :
**********************************************************************************************
*/
void process_temp_sensor_adc(void)
{
  unsigned short adc_value = 0;
  unsigned char buf[16] = {0};

  adc_value = adc_read(ADC0, CHANNEL_3);
  sprintf((char *)buf, "Temp:%2d", adc_value);
  lcd_putstring(LINE2,(char *)buf);    
}

/**
********************************************************************************************
	Function Name :	process_adc()

	Description :
	
	Input :	Void

	Output : Void

	Note :
**********************************************************************************************
*/
void process_adc(void)
{
  unsigned short adc_value = 0;
  unsigned char buf[16] = {0};

  adc_value = adc_read(ADC0, CHANNEL_2);
  sprintf((char *)buf, "ADC:%d ", adc_value);
  lcd_putstring(LINE1, (char *)buf);
}

/**
********************************************************************************************
	Function Name :	main()

	Description :
	
	Input :	Void

	Output : 

	Note :
**********************************************************************************************
*/
int main (void) 
{
  init_adc0();						// Initialize ADC
  init_lcd();						// Initialize LCD

  wait(100000);
  lcd_clear();						// clear display
  while(1)
  {
    process_adc();					// Raed ADC value and display it on first line of LCD
	process_temp_sensor_adc();		// Raed Temperature value and display it on second line of LCD
    wait(30000);
  }
}
