#include <LPC214X.h>
 	   int wait(unsigned int w)
{
	unsigned int a,b;

	for(a=0;a<w;a++)
		for(b=0;b<200;b++);
}


 int main()
 {
 
    PINSEL0 = 0;
   PINSEL1 = 0;
   PINSEL2 = 0;
   IODIR0 = 0XFFFFFFFF;
   IODIR1 = 0XFFFFFFFF;
   IOCLR1 = 0XFFFFFFFF;
  IOCLR0 = 0XFFFFFFFF;
   while(1)
   {
      
       IOSET0 = 0XFFFFFFFF;IOSET1 = 0XFFFFFFFF;
	   wait(500);
	   IOCLR0 = 0XFFFFFFFF;IOCLR1 = 0XFFFFFFFF; 
	   wait(500);      
   }
 }
 