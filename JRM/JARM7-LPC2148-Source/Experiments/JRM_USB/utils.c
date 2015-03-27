/*
   USB Firmware Upgrader

Copyright © 2006 Yuri Tiomkin
All rights reserved.

Permission to use, copy, modify, and distribute this software in source
and binary forms and its documentation for any purpose and without fee
is hereby granted, provided that the above copyright notice appear
in all copies and that both that copyright notice and this permission
notice appear in supporting documentation.

THIS SOFTWARE IS PROVIDED BY THE YURI TIOMKIN AND CONTRIBUTORS ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL YURI TIOMKIN OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.
*/

#include <LPC214x.H>              /* LPC21xx definitions */
#include "type.h"
#include "string.h"

typedef void (*IAP)(unsigned int [],unsigned int[]);

//----------------------------------------------------------------------------
void * s_memset(void * dst,  int ch, int length)
{
  register char *ptr = (char *)dst - 1;

  while(length--)
     *++ptr = ch;

  return dst;
}

//----------------------------------------------------------------------------
void * s_memcpy(void * s1, const void *s2, int n)
{
   register int mask = (int)s1 | (int)s2 | n;

   if(n == 0)
      return s1;

   if(mask & 0x1)
   {
      register const char *src = s2;
      register char *dst = s1;

      do
      {
         *dst++ = *src++;
      }while(--n);

      return s1;
   }

   if(mask & 0x2)
   {
      register const short *src = s2;
      register       short *dst = s1;

      do
      {
        *dst++ = *src++;
      }while( n -= 2);

      return s1;
   }
   else
   {
      register const int *src = s2;
      register       int *dst = s1;

      do
      {
         *dst++ = *src++;
      }while (n -= 4);

      return s1;
   }
}


U8 s_strncmp(U8 *s1,U8 *s2, U32 num)
{
 U8 retval=0;
 U32 i=0;

 for(i=0;i<num;i++)
 {
  if(*(s1+i) != *(s2+i))
  {
   retval = 1;
   break;
   }
 }
  
  return retval;
}



int divide(int a, int b)
{
  int result = 0;
  int temp = b;
  
  while (temp >= b)
  {
    temp = a - b * result++;
  }
  
  return result-1;
}

void reverse(char s[])
{
  int c, i, j;
  
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    }  
  }
  
void u_itoa( int n, char s[] )
{
  int i, sign;
  
  if(( sign = n ) < 0 )
    n = -n;
  i = 0;
  do
  {
    s[i++] = n % 10 + '0';
  } while(( n /= 10 ) > 0 );
  
  if( sign < 0  )
    s[i++] = '-';
    
  s[i] = '\0';
  reverse( s );
}

/**
**************************************************************************

****1111
  Function Name : delay()

  Description :This function suspends the tasks for specified ticks.	

  Input :  ticks:no of ticks in multiple of 1 usec
            task: task to be suspended

  Output : void

  Note :
*******************************************************************************
*/

void delay(int count)
{
  int j=0,i=0;

  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}



















