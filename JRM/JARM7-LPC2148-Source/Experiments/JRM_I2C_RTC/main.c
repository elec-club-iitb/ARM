#include <LPC214x.H>                       /* LPC21xx definitions */
#include "lcd.h"
#include "i2c.h"
#include "stdio.h"

void * s_memset(void * dst,  int ch, int length)
{
  register char *ptr = (char *)dst - 1;

  while(length--)
     *++ptr = ch;

  return dst;
}

void wait (void)  {                        /* wait function */
  int  d;

  for (d = 0; d < 2000000; d++);           /* only to delay for LED flashes */
}
void test_rtc()
{

  DATETIMEINFO wr_dti,rd_dti;

  s_memset(&wr_dti,0,sizeof(wr_dti));
  s_memset(&rd_dti,0,sizeof(rd_dti));
	
  wr_dti.year = 11;
  wr_dti.month = 01;
  wr_dti.day   = 02;
  wr_dti.hour = 05;
  wr_dti.minute = 55;
  wr_dti.second = 2;
  
  ds1307_set(&wr_dti);
  ds1307_get(&rd_dti);
}

void display_rtc_time(void)
{
  DATETIMEINFO dti;
  char buf[16] = {0};
  
  static char prev_sec_val=0xFF;
  
  ds1307_get(&dti);
  
 if(prev_sec_val!=dti.second)
 {
	sprintf(buf, "CAL:%d:%d:%d", dti.day,dti.month,dti.year);
//	lcd_line_clear(0);
	lcd_putstring(LINE1, (char *)buf);
	//prev_sec_val=dti.second;

  	sprintf(buf, "TIME:%d:%d:%d", dti.hour,dti.minute,dti.second);
	lcd_line_clear(1);
	lcd_putstring(LINE2, (char *)buf);
	prev_sec_val=dti.second;		 
  }
}


int main (void) 
{
  init_lcd();    // initialize LCD display.
  test_rtc();
  lcd_clear();

  while (1)  
  {
	display_rtc_time();
  }
}
