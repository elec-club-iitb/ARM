#ifndef __PS2_H
#define __PS2_H

/* Typerametic constants */
#define	TR_Delay_250ms		(0 << 5)
#define	TR_Delay_500ms		(1 << 5)
#define	TR_Delay_750ms		(2 << 5)
#define	TR_Delay_1000ms		(3 << 5)

#define	TR_Rate_30				0x00
#define	TR_Rate_20				0x04
#define	TR_Rate_15				0x08
#define	TR_Rate_10				0x0C
#define	TR_Rate_5					0x14



void Ps2_Init (volatile unsigned long *port, unsigned char clk_pin, unsigned char data_pin);
void Ps2_Data_Read (unsigned char *count, unsigned char *buffer);
void Ps2_Adjust_Rate (unsigned char delay, unsigned char rate);

#endif
