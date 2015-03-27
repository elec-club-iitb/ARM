#ifndef __HID_DESCRIPTOR_H_
#define __HID_DESCRIPTOR_H_


#define INT_IN_EP						0x8A
#define BULK_OUT_EP						0x05
#define BULK_IN_EP						0x82

#define MAX_PACKET_SIZE                 64
#define EP0_PACKET_SIZE                 64

#define LE_WORD(x)                    ((x)&0xFF),((x)>>8)

#define STR0LEN 						4
#define STR1LEN 						((sizeof ("JRM TECHNOLOGIES") * 2))
#define STR2LEN 						((sizeof ("JARM7 VERSION 1.0") * 2)) 

#define INTERVAL	1
#define CS_INTERFACE			0x24

static const U8 abDescriptors[] = {

// device descriptor
	0x12,
	DESC_DEVICE,
	LE_WORD(0x0200),			// bcdUSB
	0x02,						// bDeviceClass
	0x00,						// bDeviceSubClass
	0x00,						// bDeviceProtocol
	MAX_PACKET_SIZE0,			// bMaxPacketSize
	LE_WORD(0xFFFF),			// idVendor
	LE_WORD(0x0005),			// idProduct
	LE_WORD(0x0100),			// bcdDevice
	0x01,						// iManufacturer
	0x02,						// iProduct
	0x03,						// iSerialNumber
	0x01,						// bNumConfigurations

// configuration descriptor
	0x09,
	DESC_CONFIGURATION,
	LE_WORD(67),				// wTotalLength
	0x02,						// bNumInterfaces
	0x01,						// bConfigurationValue
	0x00,						// iConfiguration
	0xC0,						// bmAttributes
	0x96,						// bMaxPower
// control class interface
	0x09,
	DESC_INTERFACE,
	0x00,						// bInterfaceNumber
	0x00,						// bAlternateSetting
	0x01,						// bNumEndPoints
	0x02,						// bInterfaceClass
	0x02,						// bInterfaceSubClass
	0x01,						// bInterfaceProtocol, linux requires value of 1 for the cdc_acm module
	0x00,						// iInterface
// header functional descriptor
	0x05,
	CS_INTERFACE,
	0x00,
	LE_WORD(0x0110),
// call management functional descriptor
	0x05,
	CS_INTERFACE,
	0x01,
	0x01,						// bmCapabilities = device handles call management
	0x01,						// bDataInterface
// ACM functional descriptor
	0x04,
	CS_INTERFACE,
	0x02,
	0x02,						// bmCapabilities
// union functional descriptor
	0x05,
	CS_INTERFACE,
	0x06,
	0x00,						// bMasterInterface
	0x01,						// bSlaveInterface0
// notification EP
	0x07,
	DESC_ENDPOINT,
	INT_IN_EP,					// bEndpointAddress
	0x03,						// bmAttributes = intr
	LE_WORD(8),					// wMaxPacketSize
	0x0A,						// bInterval
// data class interface descriptor
	0x09,
	DESC_INTERFACE,
	0x01,						// bInterfaceNumber
	0x00,						// bAlternateSetting
	0x02,						// bNumEndPoints
	0x0A,						// bInterfaceClass = data
	0x00,						// bInterfaceSubClass
	0x00,						// bInterfaceProtocol
	0x00,						// iInterface
// data EP OUT
	0x07,
	DESC_ENDPOINT,
	BULK_OUT_EP,				// bEndpointAddress
	0x02,						// bmAttributes = bulk
	LE_WORD(MAX_PACKET_SIZE),	// wMaxPacketSize
	0x00,						// bInterval
// data EP in
	0x07,
	DESC_ENDPOINT,
	BULK_IN_EP,					// bEndpointAddress
	0x02,						// bmAttributes = bulk
	LE_WORD(MAX_PACKET_SIZE),	// wMaxPacketSize
	0x00,						// bInterval

// string descriptors
	0x04,
	DESC_STRING,
	LE_WORD(0x0409),

	// manufacturer string
	STR0LEN,
	DESC_STRING,
	LE_WORD(0x0409),


	STR1LEN, 0x03,
   'J', 0,
   'R', 0,
   'M', 0,
   ' ', 0,
   'T', 0,
   'E', 0,
   'C', 0,
   'H', 0,
   'N', 0,
   'O', 0,
   'L', 0,
   'O', 0,
   'G', 0,
   'I', 0,
   'E', 0,
   'S', 0,


 	STR2LEN, 0x03,
   'J', 0,
   'A', 0,
   'R', 0,
   'M', 0,
   'B', 0,
   'o', 0,
   'a', 0,
   'r', 0,
   'd', 0,
   ' ', 0,
   'V', 0,
   'E', 0,
   'R', 0,
   'S', 0,
   'I', 0,
	'O', 0,
	'N', 0,
	' ', 0,
	'1', 0,
	'.', 0,
	'0', 0,	
   
// terminating zero
	0
};
#endif /*__HID_DESCRIPTOR_H_*/





