#include <LPC214x.H>                       /* LPC21xx definitions */
#include "lpc_scb.h"
#include "lpc_config.h"
#include "timer.h"

/**
*******************************************************************
	Function Name : lpc_pll_init()

	Description   :

	Input         : Void

	Output        : None

	Note          :
********************************************************************
*/
static void lpc_pll_init(void)
{
  // set PLL multiplier & divisor.
  // values computed from config
  PLL0CFG = PLLCFG_MSEL | PLLCFG_PSEL;
  // enable PLL
  PLL0CON = PLLCON_PLLE;
  PLL0FEED = 0xAA;                       // Make it happen.  These two updates
  PLL0FEED = 0x55;                       // MUST occur in sequence.
			
  // wait for PLL lock
  while (!(PLL0STAT & PLLSTAT_LOCK))
    continue;
	
  // enable & connect PLL
  PLL0CON = PLLCON_PLLE | PLLCON_PLLC;
  PLL0FEED = 0xAA;                       // Make it happen.  These two updates
  PLL0FEED = 0x55;                       // MUST occur in sequence.
	
  // setup & enable the MAM
  MAMTIM = MAMTIM_CYCLES;
  MAMCR = MAMCR_FULL;	
  // set the peripheral bus speed
  // value computed from config.h
  VPBDIV = VPBDIV_VALUE;                // set the peripheral bus clock speed
}

int main (void) 
{
  lpc_pll_init();	// Initialize PLL and MEMMAP.
  init_timer0();	// Configure the timer for particular delay and ON/OFF the buzzer with delay as its ontime and offtime

  while (1)  
  {
  }
}
