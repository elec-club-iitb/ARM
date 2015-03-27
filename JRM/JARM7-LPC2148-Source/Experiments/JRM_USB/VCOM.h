#ifndef __VCOM_H__
#define __VCOM_H__
#include "type.h"

#define IN_FIFO_SIZE (531)
#define OUT_FIFO_SIZE 512
#define	SET_LINE_CODING         0x20
#define	GET_LINE_CODING		0x21
#define	SET_CONTROL_LINE_STATE	0x22
#define FIFO_SIZE               64

typedef struct {
	U32 dwDTERate;
	U8  bCharFormat;
	U8  bParityType;
	U8  bDataBits;
} TLineCoding;


S32 VCOM_write(U16 len, U8 *buf);
S32 VCOM_read(U16 len,U8 *buf);
void VCOM_init(void);



#endif  /* __HID_H__ */
