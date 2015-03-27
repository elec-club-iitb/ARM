#ifndef __SPIHW_H
#define __SPIHW_H

extern void SPI_init(	volatile unsigned long *spi_port,	// SPI Port
											unsigned char cs_pin,			// CS#
											unsigned char pclkdiv,		// number of PCLK cycles that make up an SPI clock.
											char bCPOL,								// clock polarity
											char bCPHA);							// clock phaze
extern void SPI_enable (void);
extern void SPI_disable (void);
extern unsigned char SPI_char (unsigned char chTx);

#endif
