#include "circular_buf.h"
#include "type.h"
#include "utils.h"

S32 CirBufInit(CIR_BUFFER *circular_buf, U32 size, U8 *ptr)
{
  U32 retval = 0;
  if ( circular_buf != NULL )
  {
    circular_buf->Buffer =ptr;
    if( circular_buf->Buffer != NULL ) 
    {                 
      circular_buf->size = size;
      circular_buf->readPos = 0;
      circular_buf->writePos = 0;
      circular_buf->overflow = 0 ;
    } 
    else 
    {
	retval = -1;
    }
  }
  else 
  {
    retval = -1 ;
  }
  return retval;
}

S32 getCirBufAvailableSize( CIR_BUFFER *circular_buf ) 
{
  U32 retval;
  if ( circular_buf != NULL )
  {
    retval = circular_buf->size - getCirBufSize (circular_buf);
  }
  else
  {
    retval = -1;
  }
  return retval;
}

S32 getCirBufSize(CIR_BUFFER *circular_buf)
{
  U32 retval= 0 ;
  if ( circular_buf != NULL )
  {
    if ( (circular_buf->readPos <= circular_buf->writePos ) && circular_buf->overflow == 0)
    {
      retval = ( circular_buf->writePos ) - circular_buf->readPos;
    }
    else if ( ( circular_buf->writePos == circular_buf->readPos ) && circular_buf->overflow == 1 )
    {
      retval = circular_buf->size ;
    }
    else
    {
      retval = (circular_buf->size - circular_buf->readPos) + circular_buf->writePos ;
    }
  }

  return retval;
}

S32 pushToCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size )
{
  S32 retval=0;
  U32 i;
  U32 BufSize=0;

  if ( circular_buf != NULL )
  {
    BufSize = getCirBufAvailableSize (circular_buf);
    if (BufSize >= size)
    {
      for(i=0; i<size ; i++)
      {
	circular_buf->Buffer[ circular_buf->writePos  ] = buffer [i] ;
	if( circular_buf->writePos+1 == circular_buf->size ) 
        {
          circular_buf->overflow = 1 ;
          circular_buf->writePos = 0 ;
	}
        else
        {
          circular_buf->writePos ++ ;
        }
      }
      retval = size;
    }
    else if(BufSize < size )
    {
      retval = BufSize;
    }
  }
  else
  {
    retval = -1;
  }

  return retval;
}

S32 peekIntoCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size)
{
  U32 retval= 0;
  U32 i;
  U32 readPosition=circular_buf->readPos;
  if ( circular_buf != NULL )	
  {		 
    if ( getCirBufSize (circular_buf) >= size )
    {
      for (i=0; i < size; i++ )
      {
        buffer[i] = circular_buf->Buffer [ readPosition ];
        readPosition ++ ;
        if ( readPosition == circular_buf->size )
        {
          readPosition = 0;
        }
      }
      retval = size;			
    }
    else 
    {
      retval = -1;
    }
  }
  else
  {
    retval = -1;
  }
  return retval;
}

S32 popFromCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size)
{
  S32 retval= 0;
  U32 i;
  U32 BufSize;

  if ( circular_buf != NULL )	
  {
     BufSize = getCirBufSize (circular_buf);
     if ( BufSize >= size )
     {
        for(i=0;i<size;i++) 
        {	
          buffer[i] = circular_buf->Buffer [ circular_buf->readPos ];
          if ( circular_buf->readPos+1 == circular_buf->size )
          {
            circular_buf->readPos = 0;
            circular_buf->overflow = 0 ;
          }
          else
          {
            circular_buf->readPos ++ ;
          }
        }    
        retval = size ;
    }
    else if(BufSize < size )
    {
      retval = BufSize;
    }
  }
  else
  {
    retval = -1;
  }

  return retval;
}

S32 flushCirBuf ( CIR_BUFFER *circular_buf )
{
  U32 retval = 0;
  if ( circular_buf !=NULL )
  {
    circular_buf->writePos = 0;
    circular_buf->readPos = 0;
    s_memset( circular_buf->Buffer, 0x0, circular_buf->size );
  }
  else
  {
    retval = -1;
  }
  return retval;
}

