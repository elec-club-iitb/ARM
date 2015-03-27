#ifndef __CAN_SPICONST_H
#define __CAN_SPICONST_H


/*********************************************************************
 *
 * enum CAN_OP_MODE
 *
 * This enumeration values define codes related to CAN module
 * operation mode. CANSetOperationMode() routine requires this code.
 * These values must be used by itself
 * i.e. it cannot be ANDed to form * multiple values.
 *
 ********************************************************************/
#define	CAN_MODE_BITS			0xE0		// Use this to access opmode  bits
#define	CAN_MODE_NORMAL		0x00
#define	CAN_MODE_SLEEP		0x20
#define	CAN_MODE_LOOP			0x40
#define	CAN_MODE_LISTEN		0x60
#define	CAN_MODE_CONFIG		0x80


/*********************************************************************
 *
 * enum CAN_TX_MSG_FLAGS
 *
 * This enumeration values define flags related to transmission of a
 * CAN message.  There could be more than one this flag
 * ANDed together to form multiple flags.
 *
 *********************************************************************/
#define	CAN_TX_PRIORITY_BITS	0x03
#define	CAN_TX_PRIORITY_0			0xFC		// XXXXXX00
#define	CAN_TX_PRIORITY_1			0xFD		// XXXXXX01
#define	CAN_TX_PRIORITY_2			0xFE		// XXXXXX10
#define	CAN_TX_PRIORITY_3			0xFF		// XXXXXX11

#define	CAN_TX_FRAME_BIT			0x08
#define	CAN_TX_STD_FRAME			0xFF		// XXXXX1XX
#define	CAN_TX_XTD_FRAME			0xF7		// XXXXX0XX

#define	CAN_TX_RTR_BIT 				0x40
#define	CAN_TX_NO_RTR_FRAME		0xFF		// X1XXXXXX
#define	CAN_TX_RTR_FRAME			0xBF		// X0XXXXXX


/*********************************************************************
 *
 * enum CAN_RX_MSG_FLAGS
 *
 * This enumeration values define flags related to reception of a CAN
 * message.  There could be more than one this flag
 * ANDed together to form multiple flags.
 * If a particular bit is set; corresponding meaning is TRUE or else
 * it will be FALSE.
 *
 * e.g.
 *      if (MsgFlag & CAN_RX_OVERFLOW)
 *
 *          // Receiver overflow has occured.  We have lost previous
 *          // message.
 *          ...
 *
 *
 ********************************************************************/
#define	CAN_RX_FILTER_BITS		0x07		// Use this to access filter bits
#define	CAN_RX_FILTER_1				0x00
#define	CAN_RX_FILTER_2				0x01
#define	CAN_RX_FILTER_3				0x02
#define	CAN_RX_FILTER_4				0x03
#define	CAN_RX_FILTER_5				0x04
#define	CAN_RX_FILTER_6				0x05

#define	CAN_RX_OVERFLOW				0x08		// Set if Overflowed else cleared
#define	CAN_RX_INVALID_MSG		0x10		// Set if invalid else cleared
#define	CAN_RX_XTD_FRAME			0x20		// Set if XTD message else cleared
#define	CAN_RX_RTR_FRAME			0x40		// Set if RTR message else cleared
#define	CAN_RX_DBL_BUFFERED		0x80		// Set if this message was hardware double-buffered




/*********************************************************************
 *
 * enum CAN_MASK
 *
 * This enumeration values define mask codes.  Routine CANSetMask()
 * requires this code as one of its arguments.  These enumerations
 * must be used by itself i.e. it cannot be ANDed to form multiple
 * values.
 *
 ********************************************************************/
#define	CAN_MASK_B1		0
#define	CAN_MASK_B2		1


/*********************************************************************
 *
 * enum CAN_FILTER
 *
 * This enumeration values define filter codes.  Routine CANSetFilter
 * requires this code as one of its arguments.  These enumerations
 * must be used by itself
 * i.e. it cannot be ANDed to form multiple values.
 *
 ********************************************************************/
#define	CAN_FILTER_B1_F1		0
#define	CAN_FILTER_B1_F2		1
#define	CAN_FILTER_B2_F1		2
#define	CAN_FILTER_B2_F2		3
#define	CAN_FILTER_B2_F3		4
#define	CAN_FILTER_B2_F4		5


/*********************************************************************
 *
 * enum CAN_CONFIG_FLAGS
 *
 * This enumeration values define flags related to configuring CAN
 * module. Routines CANInitialize() and CANSetBaudRate() use these
 * codes. One or more these values may be ANDed to form multiple
 * flags.
 *
 ********************************************************************/
#define	CAN_CONFIG_DEFAULT						0xFF		// 11111111

#define	CAN_CONFIG_PHSEG2_PRG_BIT			0x01
#define	CAN_CONFIG_PHSEG2_PRG_ON			0xFF		// XXXXXXX1
#define	CAN_CONFIG_PHSEG2_PRG_OFF			0xFE		// XXXXXXX0

#define	CAN_CONFIG_LINE_FILTER_BIT		0x02
#define	CAN_CONFIG_LINE_FILTER_ON			0xFF		// XXXXXX1X
#define	CAN_CONFIG_LINE_FILTER_OFF		0xFD		// XXXXXX0X

#define	CAN_CONFIG_SAMPLE_BIT					0x04
#define	CAN_CONFIG_SAMPLE_ONCE				0xFF		// XXXXX1XX
#define	CAN_CONFIG_SAMPLE_THRICE			0xFB		// XXXXX0XX

#define	CAN_CONFIG_MSG_TYPE_BIT				0x08
#define	CAN_CONFIG_STD_MSG						0xFF		// XXXX1XXX
#define	CAN_CONFIG_XTD_MSG						0xF7		// XXXX0XXX

#define	CAN_CONFIG_DBL_BUFFER_BIT			0x10
#define	CAN_CONFIG_DBL_BUFFER_ON			0xFF		// XXX1XXXX
#define	CAN_CONFIG_DBL_BUFFER_OFF			0xEF		// XXX0XXXX

#define	CAN_CONFIG_MSG_BITS						0x60
#define	CAN_CONFIG_ALL_MSG						0xFF		// X11XXXXX
#define	CAN_CONFIG_VALID_XTD_MSG			0xDF		// X10XXXXX
#define	CAN_CONFIG_VALID_STD_MSG			0xBF		// X01XXXXX
#define	CAN_CONFIG_ALL_VALID_MSG			0x9F		// X00XXXXX


#endif
