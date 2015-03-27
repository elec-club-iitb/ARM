#include <LPC214x.H>                       /* LPC21xx definitions */
#include "Ext_Int.h"
#include "buzzer.h"

#define EXTINT_EINT1_MASK 0x2
#define EXTPOLAR_EXTPOLAR1_MASK 0x2
#define EXTMODE_EXTMODE1_MASK 0x2

// Vector Control Register bit definitions
#define VIC_ENABLE      (1 << 5)

// Convert Channel Number to Bit Value
#define VIC_BIT(chan)   (1 << (chan))
#define VIC_EINT1       15

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

/**
********************************************************************************************
  Function Name :	key_init()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void keypad_init()
{
  KEYPAD_DATA_DIR &= ~(ROW_MASK | COL_MASK);      
  KEYPAD_DATA_DIR |= COL_MASK;                    //make Rows as i/p and cols are 0/p

  EXTMODE = EXTMODE_EXTMODE1_MASK;
  
  EXTPOLAR &= ~EXTPOLAR_EXTPOLAR1_MASK;

  PINSEL0 = (PINSEL0 & ~(3 << 28)) | (1 << 29);
  
  /* initialize the interrupt vector */
  VICIntSelect &= ~ VIC_BIT(VIC_EINT1);           // EINT0 selected as IRQ
  VICVectAddr5 = (unsigned int)Ext_ISR;        // address of the ISR
  VICVectCntl5 = VIC_ENABLE | VIC_EINT1;
  VICIntEnable = VIC_BIT(VIC_EINT1);              // EINT0 interrupt enabled

  EXTINT &= ~EXTINT_EINT1_MASK;	
}

/**
********************************************************************************************
  Function Name :	keypad_ISR()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void Ext_ISR() __irq
{
	turn_on_buzzer();
	delay(10000);
    turn_off_buzzer();

	EXTINT |= EXTINT_EINT1_MASK;                                 //clear interrupt
	VICVectAddr = 0; 
}

