#ifndef __ENC28J60_H
#define __ENC28J60_H


#define ENC28J60_HALFDUPLEX		0
#define ENC28J60_FULLDUPLEX		1


extern void						ENC28J60_Init(volatile unsigned long *RSTportPtr, unsigned long RSTbit, volatile unsigned long *CSport, unsigned long CSbit, unsigned char *mac, unsigned char *ip, unsigned char fullDuplex);
extern void						ENC28J60_doPacket(void);
extern void						ENC28J60_putByte(unsigned char b);
extern unsigned char	ENC28J60_getByte(void);
extern unsigned long	ENC28J60_userUDP(unsigned char *remoteHost, unsigned long remotePort, unsigned long localPort, unsigned long reqLength);
extern unsigned long	ENC28J60_userTCP(unsigned char *remoteHost, unsigned long remotePort, unsigned long localPort, unsigned long reqLength);


#endif
