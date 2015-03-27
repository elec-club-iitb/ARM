#ifndef __LCD8_H
#define __LCD8_H


void LCD8_init(	volatile unsigned long *ctrl_port,	// Control port
								volatile unsigned long *data_port,	// DATA port
								unsigned char rs_pin,			// RS
								unsigned char rw_pin,			// RW
								unsigned char e_pin,			// E
								unsigned char D0_pin);		// D0 bit position (8-bit data bus D[7..0])
void LCD8_sendstr (char x, char y, const unsigned char *p);


#endif
