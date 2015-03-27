#ifndef __CF_H
#define __CF_H


void Cf_Init(	volatile unsigned long *ctrl_port,			// Control lines port
							volatile unsigned long *data_port,			// Data lines port
							unsigned char a0_pin,					// 1st line position on control port (A0)
							unsigned char d0_pin);				// 1st line position on data port (D0)
unsigned char Cf_Detect(void);
void Cf_Read_Sector(unsigned long sector_number, unsigned char *buffer);
void Cf_Write_Sector(unsigned long sector_number, unsigned char *buffer);



#endif
