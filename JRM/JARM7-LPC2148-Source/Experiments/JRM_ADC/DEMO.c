/*
 * Project name:
     DEMO (Using Internal A/D Converter)
 * Copyright
     (c) Mikroelektronika, 2008.
 * Description:
     This is a simple project.
		 Analog value is converted and displayed on PORT1[25..16] (10-bit value)
		 LSB is P0.16
		 MSB is P0.25
 * Test configuration:
     MCU:             LPC2148
     Dev.Board:       EasyARM
     Oscillator:      12.0 MHz (cclk = 60.0 MHz, Fcco = 240.0 MHz)
     Ext. Modules:    -
     SW:              KEIL uVision3 v3.62c
 * NOTES:
     - Place Pull-up Jumper J16 at PORT0[15..8]
     - Turn ON LEDs on PORT1 (Switch SW2).
*/


#include <LPC214X.H>

#include "Utility.h"



//**************************************************************************************************
//
// ADC Routines
//
//**************************************************************************************************
void ADC_Init()
{
	// Initial AD0.3,AD0.2 (P0.30,P0.29) By Set PINSEL1[29:28=01, 27:26=01] 
	// xx01 01xx xxxx xxxx xxxx xxxx xxxx xxxx
	PINSEL1 &= 0xD7FFFFFF;
	PINSEL1 |= 0x14000000;
	// set PDA0 (Enable Power to ADC0)
	PCONP |= (unsigned long)(0x00000001) << 12;
 
	// Enable ADC0
	AD0CR &= 0x00000000;		// Clear All Bit Control
	AD0CR |= 0x00000008;		// Select ADC = AD0.3
	AD0CR |= 0x00000700;		// ADC Clock = VBP(PCLK) / 8
	AD0CR &= 0xFFFEFFFF;		// Busrt = 0			- Conversions are software controlled and reguire 11 clocks
	AD0CR &= 0xFFF1FFFF;		// CLKS  = 000		- 10Bit : 11 Cycle Clock Conversion
	AD0CR |= 0x00200000;		// PDN   = 1			- Active ADC Module
	// Disable ADC1
	AD1CR = 0;
}


unsigned long ADC_Get2()
{
	unsigned long	val;

	// Select ADC = AD0.2
	AD0CR &= 0xFFFFFF00;
	AD0CR |= 0x00000004;
	// START = 001 = Start Conversion Now
	AD0CR |= 0x01000000;
	// Wait ADC Conversion to Complete and Read A/D Data Register
	do {
		DelayProc(25.0E-06 * CCLOCK);
	} while ((AD0GDR & 0x80000000) == 0);
	// Shift ADC Result to Integer
	val = (AD0DR2 >> 6) & 0x000003FF;
	AD0CR &= 0xF8FFFFFF;

	return (val);
}


unsigned long ADC_Get3()
{
	unsigned long	val;

	// Select ADC = AD0.3
	AD0CR &= 0xFFFFFF00;
	AD0CR |= 0x00000008;
	// START = 001 = Start Conversion Now
	AD0CR |= 0x01000000;
	// Wait ADC Conversion to Complete and Read A/D Data Register
	do {
		DelayProc(25.0E-06 * CCLOCK);
	} while ((AD0GDR & 0x80000000) == 0);
	// Shift ADC Result to Integer
	val = (AD0DR3 >> 6) & 0x000003FF;
	AD0CR &= 0xF8FFFFFF;

	return (val);
}
//**************************************************************************************************




int main (void)
{
	PINSEL0 = 0;
	PINSEL1 = 0;
	//PINSEL2 &= 0x0000000C;
//	PINSEL2 |= 0x00000030;
	PINSEL2 = 0;

	DelayProc(0.2 * CCLOCK);


	// Initialize Internal ADC
	ADC_Init();

	// PORT1[31..16] defined as Output
	IODIR1 = 0xFFFFFFFF;

  // Start Test Read AD0.3 and Display LEDs
  while(1)
		{
		IOPIN1 = ((ADC_Get3() << 16) & 0xFFFF0000);
		DelayProc(0.250 * CCLOCK);
		}
}
