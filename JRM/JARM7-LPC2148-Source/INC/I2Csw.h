#ifndef __I2CSW_H
#define __I2CSW_H


void Soft_I2C_Init(	volatile unsigned long *i2c_port,		// I2C Port
										unsigned char sda_pin,			// SDA
										unsigned char scl_pin);			// SCL
char Soft_I2C_Send(char Address, unsigned char *Data, char Num);
char Soft_I2C_Read(char Address, unsigned char *Data, char Num);


#endif
