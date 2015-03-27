#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include "type.h"

typedef struct __CIR_BUFFER {
  U8 *Buffer; 
  U32 size;
  U32 readPos;
  U32 writePos;
  U32 overflow;
} CIR_BUFFER;
S32 pushToCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size );
S32 CirBufInit (CIR_BUFFER *circular_buf, U32 size,U8 *ptr);
S32 peekIntoCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size);
S32 popFromCirBuf(CIR_BUFFER *circular_buf, U8 *buffer, U32 size);
S32 getCirBufAvailableSize ( CIR_BUFFER *circular_buf );
S32 flushCirBuf ( CIR_BUFFER *circular_buf );
S32 getCirBufSize(CIR_BUFFER *circular_buf);

#endif
