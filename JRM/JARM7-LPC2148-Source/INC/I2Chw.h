#ifndef __I2CHW_H
#define __I2CHW_H


void I2C_Init(void);
char I2C_Read(char Address, unsigned char *Data, char Num);
char I2C_Send(char Address, unsigned char *Data, char Num);


#endif
