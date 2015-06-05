#ifndef PROCESS_H_
	#define PROCESS_H_
	#include <string.h>
// process according to serial buffer received .
 static int processes=0;
class processor{
	private:
		
		
		void (*processList [10])(void);
		char * processName [10];
	public:
		processor();
		void add( void (*f)(void), char * processName);
		bool process(char * cmd);
		void remove(char * processName);
};
#endif