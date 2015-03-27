#ifndef __LCD4_H
#define __LCD4_H


void LCD4_init(	volatile unsigned long *port,			// DATA port
								unsigned char D4_pin,			// D4 bit position (4-bit data bus D[7..4])
								unsigned char rs_pin,			// RS
								unsigned char e_pin);			// E
void LCD4_sendstr (char x, char y, const unsigned char *p);


#endif
