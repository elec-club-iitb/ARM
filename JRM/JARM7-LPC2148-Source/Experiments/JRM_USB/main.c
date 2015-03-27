#include <LPC214x.H>              /* LPC21xx definitions */
#include "type.h"
#include "vcom.h"
#include "usbapi.h"

#define USB_TEXT "\n\r Testing USB JRM JARM7 Board\n\r JARM7 Board Revision : 1.0 \n\r Firmware Version: 1.0 \n\r For more information on JARM7 visit www.jrmtech.in"

/**
*******************************************************************
	Funtion Name : test_usb()

	Description  : 

	Input        : 

	Output       : None

	Note         :
*****************************************************************
*/
void test_usb(void)
{
  U8 buffer[] = USB_TEXT;

  while((VCOM_write(sizeof(buffer), buffer)) != sizeof(buffer));
}

int main (void) 
{
	U8 ch = 0;

	SCS = 3;    //sets port 1 and 0 to fast mode (not compatable with previous LPCs)

	VCOM_init();
	
	while (1)
	{
	    if(get_USB_enumeration_status())
	    {
			if(VCOM_read(sizeof(ch),&ch))
			{
				test_usb();
			}
	    }	
	}
}
