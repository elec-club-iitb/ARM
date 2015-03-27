#include <LPC214x.H>              /* LPC21xx definitions */
#include "type.h"
#include "usbdebug.h"
#include "usbapi.h"
//#include "tn.h"
#include "usbdesc.h"
#include "VCOM.h"
#include "string.h"
#include "Circular_buf.h"
#include "utils.h"

static U8 abClassReqData[4];
static U32 _iIdleRate = 0;
static TLineCoding LineCoding = {115200, 0, 0, 8};
static U8 abBulkBuf[64];

U8 in_fifo_ptr[IN_FIFO_SIZE];
U8 out_fifo_ptr[OUT_FIFO_SIZE];

CIR_BUFFER in_circular_buf;
CIR_BUFFER out_circular_buf;

/**
*****************************************************************
	Function Name :	HandleClassRequest()

	Description :	HID class request handler

	Input :	TSetupPacket *pSetup (pointer to structure of setup packet),  int *piLen, U8 **ppbData.

	Output : int (TRUE OR FALSE) Value .

	Note :	Function is static
*****************************************************************
*/	

static S32 HandleClassRequest(TSetupPacket *pSetup, int *piLen, U8 **ppbData)
{
  U8 *pbData = *ppbData;
  switch (pSetup->bRequest) {

    case HID_GET_IDLE:
      DBG("GET IDLE, val=%X, idx=%X\n", pSetup->wValue, pSetup->wIndex);
      pbData[0] = (_iIdleRate / 4) & 0xFF;
      *piLen = 1;
      break;

    case HID_SET_IDLE:
      DBG("SET IDLE, val=%X, idx=%X\n", pSetup->wValue, pSetup->wIndex);
      _iIdleRate = ((pSetup->wValue >> 8) & 0xFF) * 4;
      break;

    case SET_LINE_CODING:
      DBG("SET_LINE_CODING\n");
      s_memcpy((U8 *)&LineCoding, *ppbData, 7);
      *piLen = 7;
      DBG("dwDTERate=%u, bCharFormat=%u, bParityType=%u, bDataBits=%u\n",
      LineCoding.dwDTERate,
      LineCoding.bCharFormat,
      LineCoding.bParityType,
      LineCoding.bDataBits);
      break;
    
    case GET_LINE_CODING:
      DBG("GET_LINE_CODING\n");
      *ppbData = (U8 *)&LineCoding;
      *piLen = 7;
      break;
    
    case SET_CONTROL_LINE_STATE:
      // bit0 = DTR, bit = RTS
      DBG("SET_CONTROL_LINE_STATE %X\n", pSetup->wValue);
      break;		
    default:
      DBG("Unhandled class %X\n", pSetup->bRequest);
      return FALSE;
  }
  return TRUE;
}

/**
*****************************************************************
	Function Name : BulkOut()

	Description   :

	Input         : bEP,bEPStatus

	Output        :None

	Note          :
*****************************************************************
*/
      
static void BulkOut(U8 bEP, U8 bEPStatus)
{
  U32  iLen=0;
  if((bEPStatus&EP_STATUS_DATA))
  {
    // get data from USB into intermediate buffer
    iLen = USBHwEPRead(bEP, (U8 *)abBulkBuf, sizeof(abBulkBuf));
    pushToCirBuf(&in_circular_buf, abBulkBuf, iLen);
  }
}

/**
*****************************************************************
	Function Name : BulkIn()

	Description   : 

	Input         : bEP,bEPStatus

	Output        : None

	Note          :
*****************************************************************
*/

static void BulkIn(U8 bEP, U8 bEPStatus)
{
  S32 len=0;

  len = popFromCirBuf(&out_circular_buf, abBulkBuf, MAX_PACKET_SIZE);
  
  if(len > 0)
  {
    if(len < MAX_PACKET_SIZE)
    {
      /* Note: If available number of bytes in the circulare buffer
      is less than the requested, the pop functions returns the number 
      of bytes that are currently availabe, but does not pop it out 
      from the buffer. Hence need to pop it here */
      popFromCirBuf(&out_circular_buf, abBulkBuf, len);
    }
    USBHwEPWrite(bEP, (U8*)abBulkBuf, len);
  }
  if (len < MAX_PACKET_SIZE)
  {
    USBHwNakIntEnable(0);
  }
}

/**
*****************************************************************
	Function Name : VCOM_init()

	Description   : 

	Input         : void

	Output        : none

	Note          :
*****************************************************************
*/

void VCOM_init(void)
{
  if (!get_USB_enumeration_status())
  {
    DBG("Initialising USB stack\n");
		USBInit();
		
    // register device descriptors
    USBRegisterDescriptors(abDescriptors);
    // register class request handler
    USBRegisterRequestHandler(REQTYPE_TYPE_CLASS, HandleClassRequest, abClassReqData);
    USBHwRegisterEPIntHandler(BULK_OUT_EP, BulkOut);
    USBHwRegisterEPIntHandler(BULK_IN_EP, BulkIn);
    USBHwNakIntEnable(INACK_BI);
    USBHwConfigureEPasFastInt(BULK_IN_EP);
    CirBufInit(&in_circular_buf, IN_FIFO_SIZE, in_fifo_ptr);
    CirBufInit(&out_circular_buf, OUT_FIFO_SIZE, out_fifo_ptr);
    // connect to bus
    USBHwConnect(TRUE);
  }
}

/**
*******************************************************************
	Funtion Name : VCOM_read()

	Description  : 

	Input        : length,buffer

	Output       : None

	Note         :
*****************************************************************
*/

S32 VCOM_read(U16 len,U8 *buf)
{
  S32 retval=0;
 
  if(get_USB_enumeration_status())
  {
    retval = popFromCirBuf(&in_circular_buf, buf, len);

    if( (retval >0) && (retval < len))
    {
      popFromCirBuf(&in_circular_buf, buf, retval);
    }
  }

  return retval;
}

/**
*******************************************************************
	Funtion Name : VCOM_write()

	Description  : 

	Input        : length,buffer

	Output       : None

	Note         :
*****************************************************************
*/

S32 VCOM_write(U16 len, U8 *buf)
{
  S32 retval=0;

  if(get_USB_enumeration_status())
  {
    retval = pushToCirBuf(&out_circular_buf, buf, len);
    
    if(retval == len)
    {
      USBHwNakIntEnable(INACK_BI);
    }
  }
  return retval;
}

