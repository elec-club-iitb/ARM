//#include "lpc_vic.h"
#include "timer.h"
//#include "tn.h"
#include "buzzer.h"

void (*timer1_cb)(void);

/**
*******************************************************************************
  Function Name :	init_timer0()

  Description :This function initialises the timer0 as system tick
              The minimum tick for which the timer0 is configured is 10msec

  Input :	
		            
  Output :	void

  Note :
*******************************************************************************
*/	
void init_timer0(void)
{

//--- Timer 0  - interrupt 10 ms
  T0PR = 0;  //-- Prscaler = 0
  T0PC = 0;
  //T0MR0 = 60000 * 10;  //clock rate of 60000 * 10ms ?
  T0MR0 = 6000000 ; // 100ms
  T0MCR = 3; //-- bit 0=1 -int on MR0 , bit 1=1 - Reset on MR0
  T0TCR = 1; //-- Timer 0 - run
  VICIntSelect &= ~ VIC_BIT(VIC_TIMER0);
  VICVectAddr0 = (unsigned int)timer0_int_func;   //-- Timer 0 int - priority top-1
  VICVectCntl0 = VIC_ENABLE | VIC_TIMER0;
  VICIntEnable |= VIC_BIT(VIC_TIMER0);
}





/**
*******************************************************************************
  Function Name :	timer1_int_func()

  Description : This is the timer1 interrupt handler. It will invoke the 
                callback function if registered.

  Input : None           
  Output : None

  Note :
*******************************************************************************
*/
void timer1_int_func(void)
{
  T1IR = 0xFF;

  //uclk_handler ( );

   VICVectAddr = 0xFF;
}

/**
********************************************************************************
	Function Name : tn_timer_int_func()

	Description   :

	Input         : Void

	Output	      : None

	Note          :
********************************************************************************
*/
void timer0_int_func(void) __irq
{
	static unsigned char flag = 0;

	T0IR = 0xFF;                //-- clear int source
	if(flag)
	{
		turn_on_buzzer();
		flag = 0;
	}
	else
	{
		turn_off_buzzer();
		flag = 1;
	}

   VICVectAddr = 0xFF;
}


