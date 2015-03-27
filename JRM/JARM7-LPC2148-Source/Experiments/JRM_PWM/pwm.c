#include "LPC214x.H"                        /* LPC21xx definitions */
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

unsigned long match_counter;

/******************************************************************************
** Function name:		PWMHandler
**
** Descriptions:		PWM interrupt handler
**				For now, it only deals with PWM match 0
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void PWMHandler (void) __irq 
{
    unsigned long regVal;

    regVal = PWMIR;
    IENABLE;			/* handles nested interrupt */
    if ( regVal & MR0_INT )
    {
	match_counter++;	
    }
    PWMIR |= regVal;		/* clear interrupt flag on match 0 */
    IDISABLE;
    VICVectAddr = 0;		/* Acknowledge Interrupt */
}

/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,
**				reset counter, all latches are enabled, interrupt
**				on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			Duty cycle
** Returned value:		true or fase, if VIC table is full, return false
** 
******************************************************************************/
unsigned long PWM_Init( unsigned long cycle )
{
    match_counter = 0;
    PINSEL0 |= 0x000A800A;	/* set GPIOs for all PWMs */

    PINSEL1 = 0x00000400;

    PWMTCR = TCR_RESET;		/* Counter Reset */ 
		
    PWMPR = 0x00;		/* count frequency:Fpclk */
    PWMMCR = PWMMR0I | PWMMR0R;	/* interrupt on PWMMR0, reset on PWMMR0, reset 
				TC if PWM0 matches */				
    PWMMR0 = cycle;		/* set PWM cycle */
    PWMMR1 = cycle * 5/6;
    PWMMR2 = cycle * 2/3;
    PWMMR3 = cycle * 1/2;
    PWMMR4 = cycle * 1/3;
    PWMMR5 = cycle * 1/6;	

    /* all PWM latch enabled */
    PWMLER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;

    if ( install_irq( PWM0_INT, (void *)PWMHandler ) == FALSE )
    {
		return (FALSE);
    }
    return (TRUE);
}

/******************************************************************************
** Function name:		PWM_Set
**
** Descriptions:		PWM cycle setup
**
** parameters:			PWM cycle and offset
** Returned value:		None
** 
******************************************************************************/
void PWM_Set( unsigned long cycle, unsigned long offset )
{			
    PWMMR0 = cycle;		/* set PWM cycle */
    PWMMR1 = cycle * 5/6 + offset;
    PWMMR2 = cycle * 2/3 + offset;
    PWMMR3 = cycle * 1/2 + offset;
    PWMMR4 = cycle * 1/3 + offset;
    PWMMR5 = cycle * 1/6 + offset;

    /* The LER will be cleared when the Match 0 takes place, in order to
    load and execute the new value of match registers, all the PWMLERs need to
    reloaded. all PWM latch enabled */
    PWMLER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;    
    return;
}

/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void PWM_Start( void )
{
    /* All single edge, all enable */
    PWMPCR = PWMENA1 | PWMENA2 | PWMENA3 | PWMENA4 | PWMENA5 | PWMENA6;
    PWMTCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */
    return;
}

/******************************************************************************
** Function name:		PWM_Stop
**
** Descriptions:		Stop all PWM channels
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void PWM_Stop( void )
{
    PWMPCR = 0;
    PWMTCR = 0x00;		/* Stop all PWMs */
    return;
}

