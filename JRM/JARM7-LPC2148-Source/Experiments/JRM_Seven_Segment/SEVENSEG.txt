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
   IODIR1 = 0XFFFFFFFF;
   IOCLR1 = 0XFFFFFFFF;

   while(1)
   {
      
       IOSET1= 0x01370000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	    IOSET1= 0x025F0000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	    IOSET1= 0x04720000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	    IOSET1= 0x08060000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	    IOSET1= 0x105F0000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	    IOSET1= 0x206D0000;
	   wait(200);
	   IOCLR1 = 0xFFFFFFFF;
	   wait(200);
	  
       
   }
 }
 