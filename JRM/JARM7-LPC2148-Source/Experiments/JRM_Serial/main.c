#include <stdio.h>                /* prototype declarations for I/O functions */
#include <LPC214x.H>              /* LPC21xx definitions                      */
#include "Serial.h"

/**
**************************************************************************

****1111
  Function Name : delay()

  Description :This function suspends the tasks for specified ticks.	

  Input :  ticks:no of ticks in multiple of 1 usec
            task: task to be suspended

  Output : void

  Note :
*******************************************************************************
*/

void delay(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}

/****************/
/* main program */
/****************/
int main (void)  {                /* execution starts here                    */

  uart0_init();					  // Initialize UART0
  uart1_init();					  // Initialize UART0

  while (1) {                          /* An embedded program does not stop */
  uart0_puts ("JRM UART0 OK\n\r");	  // Transffer data to PC through Serial
  uart1_puts ("JRM UART1 OK\n\r");	  // Transffer data to PC through Serial
  delay(100000);
  }                               
}
