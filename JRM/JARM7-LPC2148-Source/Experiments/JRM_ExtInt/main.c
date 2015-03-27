#include <LPC214x.H>                       /* LPC21xx definitions */
#include "ext_int.h"

int main (void) 
{
  keypad_init();   // initialize the keypad in interrup mode

  while (1)  
  {
  }
}
