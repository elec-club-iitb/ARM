#ifndef __ONEWIRE_H
#define __ONEWIRE_H


void ow_init(	volatile unsigned long *ow_port,		// OW port
							unsigned char dq_pin);		// OW pin
unsigned char ow_reset(void);
unsigned char ow_read(void);
void ow_write(unsigned char val);


#endif
