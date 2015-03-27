#ifndef __CAN_SPISW_H
#define __CAN_SPISW_H


void CANSPIInitialize(char SJW,
											char BRP,
											char PHSEG1,
											char PHSEG2,
											char PROPSEG,
											char CAN_CONFIG_FLAGS);
void CANSPISetOperationMode(char mode, char WAIT);
char CANSPIGetOperationMode(void);
void CANSPISetBaudRate(	char SJW,
												char BRP,
												char PHSEG1,
												char PHSEG2,
												char PROPSEG,
												char CAN_CONFIG_FLAGS);
void CANSPISetMask(char CAN_MASK, unsigned long val, char CAN_CONFIG_FLAGS);
void CANSPISetFilter(char CAN_FILTER, unsigned long val, char CAN_CONFIG_FLAGS);
unsigned char CANSPIRead(	unsigned long *id,
													unsigned char *data,
													unsigned char *data_len,
													unsigned char *CAN_RX_MSG_FLAGS);
unsigned char CANSPIWrite(	unsigned long id,
														unsigned char *data,
														unsigned char data_len,
														unsigned char CAN_TX_MSG_FLAGS);


#endif
