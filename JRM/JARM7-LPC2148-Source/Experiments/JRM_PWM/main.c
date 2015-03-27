/*****************************************************************************
 *   pwmtest.c:  main C entry file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <LPC214x.H>              /* LPC21xx definitions                      */
#include "irq.h"
#include "timer.h"
#include "pwm.h"

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define LED1 (1 << 4)
#define LED2 (1 << 5)
#define LED3 (1 << 6)
#define LED4 (1 << 7)
#define LED5 (1 << 10)
#define LED6 (1 << 11)
#define LED7 (1 << 12)
#define LED8 (1 << 13)

#define LED_MASK (LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 | LED8)

#define LED_IO_DIR IODIR0
#define LED_SET IOSET0
#define LED_CLR IOCLR0

#define INIT_LEDS()     (LED_IO_DIR |= LED_MASK)

extern unsigned long timer_counter;
extern unsigned long match_counter;

/**
*****************************************************************************
	Function Name : turn_off_all_leds()

	Description   :

	Input         : Void 

	Output        : None

	Note          :
******************************************************************************
*/
void turn_off_all_leds()
{
  LED_CLR |= LED_MASK;
}

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{	    
    unsigned long cycle = PWM_CYCLE, offset = 0;

    INIT_LEDS();           // initialize the GPIO's connected to LEDs
    turn_off_all_leds();   // Turnoff all LEDs
    init_VIC();            // Initialize Vectored interrupts

    if ( PWM_Init( 0 ) != TRUE )
    {
		while( 1 );			/* fatal error */
    }

    PWM_Set( cycle, offset );
    PWM_Start();

    while ( 1 )
    {
		if ( match_counter != 0 )
		{
		    match_counter = 0;
		    if( offset <= PWM_CYCLE )
			{
				offset += PWM_OFFSET;
			}
		    else
			{
				offset = 0;
			}
	    	PWM_Set( cycle, offset );
		}
	}
    PWM_Stop() ;
	
    return 0;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
