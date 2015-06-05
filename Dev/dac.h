#ifndef DAC_H
#define DAC_H

#include <lpc214x.h>
class dacClass{
	public:
		dacClass();
		void init(void);
		void write(int value);
};
#endif