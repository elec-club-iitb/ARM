//adc library header file
#ifndef ADC_H
	#define ADC_H
	#include <lpc214x.h>
	class adc0Class
	{
		public:
			adc0Class();
			int read(int pin,int _clkdiv,int clockPerConversion=11);
			
			
	};
#endif

