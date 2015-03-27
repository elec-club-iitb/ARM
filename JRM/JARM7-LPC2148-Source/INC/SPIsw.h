#ifndef __SPISW_H
#define __SPISW_H

extern void SPI_init(	volatile unsigned long *spi_port,	// SPI Port
											unsigned char cs_pin,			// CS#
											unsigned char miso_pin,		// MISO
											unsigned char mosi_pin,		// MOSI
											unsigned char sck_pin,		// SCK
											char bCPOL,
											char bCPHA);
extern void SPI_enable (void);
extern void SPI_disable (void);
extern unsigned char SPI_char (unsigned char chTx);

#endif
