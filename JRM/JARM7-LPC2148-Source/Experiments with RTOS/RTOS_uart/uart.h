
//------------------------------------------------------------------------------------------------//
// Program		: Library for serial communication(UART)   
// Description 	: Library for about serial communication UART0 and UART1 of LPC2148
// Frequency	: Crystal 12 MHz at PLL 5x(CCLK = 60 MHz),PCLK = 30 MHz 
// Filename		: uart.h
// C compiler	: Keil CARM Compiler
//------------------------------------------------------------------------------------------------//
extern void uart1_init (unsigned int);
extern void uart0_init (unsigned int);
extern void uart1_putc	(char);
extern void uart0_putc	(char);
extern void uart1_puts	(char *);
extern void uart0_puts	(char *);

