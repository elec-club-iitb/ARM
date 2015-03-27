#include <LPC214x.H>                       /* LPC21xx definitions */

#define BUZZER (1 << 26)
#define BUZZER_DIR IODIR1
#define BUZZER_SET IOSET1
#define BUZZER_CLR IOCLR1

/**
********************************************************************************************
  Function Name :	turn_on_buzzer()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void turn_on_buzzer()
{    
  BUZZER_DIR |= BUZZER;
  BUZZER_SET |= BUZZER;	
}			 

/**
********************************************************************************************
 Function Name : turn_off_lcd_back_light()

 Description   :	

 Input         :	

 Output        : Void

 Note          :
********************************************************************************************
*/
void turn_off_buzzer(void)
{
   BUZZER_DIR |= BUZZER;
   BUZZER_CLR |= BUZZER;
}



