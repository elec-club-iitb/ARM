#include <LPC214x.H>                       /* LPC214x definitions */
#include "lcd.h"
#include "i2c.h"

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
*******************************************************************
	Funtion Name : test_i2c_at24c256_flash()

	Description  : 

	Input        : 

	Output       : None

	Note         :
*****************************************************************
*/

void test_i2c_at24c04_flash(void)
{
  unsigned char i=0;
  unsigned char status=1;
  unsigned char buf[128];

  for(i=0;i<sizeof(buf);i++)
    buf[i] = i;
  
  m24xx_write(EEPROM_24XX04, 0 , 0 , (char *)buf , sizeof(buf));

  for(i=0;i<sizeof(buf);i++)
    buf[i] = 0;

  m24xx_read(EEPROM_24XX04, 0 , 0 , (char *)buf , sizeof(buf));

  for(i=0;i<sizeof(buf);i++)
  {
    if(buf[i] != i)
    {
      status = 0;
      break;
    }    
  }

  if(status == 1)
  {
    lcd_clear();
    lcd_putstring(LINE2,"I2C FLASH PASS");
  }
  else
  {
    lcd_clear();
		lcd_putstring(LINE2,"I2C FLASH FAIL");
  }
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
  init_lcd();						// Initialize LCD
  i2c_lpc_init(I2C_SPEED_100);		// Initialize I2C

  wait(100000);
  lcd_clear();
  test_i2c_at24c04_flash();	   // Test I2C EEPROM by wrinting some data at some address and reading the same from same address
								   
  while(1)
  {
  }
}
