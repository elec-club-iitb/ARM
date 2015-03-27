#include <LPC214x.H>                       /* LPC21xx definitions */
#include "lcd.h"
#include "keypad.h"

void wait (void)  {                        /* wait function */
  int  d;

  for (d = 0; d < 2000000; d++);           /* only to delay for LED flashes */
}


int main (void) 
{
  init_lcd();    // initialize LCD display.
  keypad_init(); // initialize keypad in pole mode.

  while (1)  
  {
    keypad_poll(); // Keep poling for particular key in matrix keypad.
  }
}
