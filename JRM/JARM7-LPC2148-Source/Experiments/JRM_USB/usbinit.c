/*
	LPCUSB, an USB device driver for LPC microcontrollers	
	Copyright (C) 2006 Bertrik Sikken (bertrik@sikken.nl)

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, 
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


/** @file
	USB stack initialisation
 */

#include "type.h"
#include "usbdebug.h"
#include "usbapi.h"

static U8 usb_cable_connected = 0;
/** data storage area for standard requests */
static U8	abStdReqData[8];


/**
	USB reset handler
	
	@param [in] bDevStatus	Device status
 */
static void HandleUsbReset(U8 bDevStatus)
{
	if (bDevStatus & DEV_STATUS_RESET) {
		DBG("\n!");
		usb_cable_connected = TRUE;
	}
}


/**
	Initialises the USB hardware and sets up the USB stack by
	installing default callbacks.
	
	@return TRUE if initialisation was successful
 */
int USBInit(void)
{
	// init hardware
	USBHwInit();
	// register bus reset handler
	USBHwRegisterDevIntHandler(HandleUsbReset);
	
	// register control transfer handler on EP0
	USBHwRegisterEPIntHandler(0x00, USBHandleControlTransfer);
	USBHwRegisterEPIntHandler(0x80, USBHandleControlTransfer);
	
	// register standard request handler
	USBRegisterRequestHandler(REQTYPE_TYPE_STANDARD, USBHandleStandardRequest, abStdReqData);

	return TRUE;
}

U8 is_usb_cable_connected(void)
{
  return usb_cable_connected;
}


