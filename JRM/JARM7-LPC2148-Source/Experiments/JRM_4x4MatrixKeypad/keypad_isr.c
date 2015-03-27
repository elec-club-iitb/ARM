#include <stdio.h>
#include <LPC214x.H>                       /* LPC21xx definitions */
#include "keypad.h"
#include "lcd.h"
#include "buzzer.h"

#define KEYPAD_TIMEOUT 300

//struct uclk keypad_timer;
static unsigned  char key = KEY_NOT_PRESSED;

/**
********************************************************************************************
  Function Name :	stop_keypad_timer()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void stop_keypad_timer(void)
{
#if 0
  keypad_timer.repeat = 0;
  dereg_uclk(&keypad_timer);
#endif	
}

/**
********************************************************************************************
  Function Name :	keypad_routine_cb()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void keypad_routine_cb()
{
#if 0
  key = read_key();
  if(key == KEY_NOT_PRESSED)
    stop_keypad_timer();
  else
    post_imessage_queue(&key);

  EXTINT |= EXTPOLAR_EXTPOLAR1_MASK;
#endif	
}

/**
********************************************************************************************
  Function Name :	start_keypad_timer()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void start_keypad_timer(unsigned int  timeout)
{
#if 0
  def_uclk(&keypad_timer);
  keypad_timer.repeat = 1;
  keypad_timer.ticks = timeout;
  keypad_timer.function_callback = keypad_routine_cb;
  reg_uclk(&keypad_timer);  
#endif	
}

void keypad_poll() 
{
  unsigned  char buf[16];

  key = read_key();

  if(key <= 16)
  {
    turn_off_buzzer();
	lcd_clear();
    sprintf((char *)buf,"Key Num : %u",key);
    lcd_putstring(LINE1,(char *)buf);
    turn_on_buzzer();		
  }
}





