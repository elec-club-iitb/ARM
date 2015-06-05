#include "process.h"
processor::processor()
{
}
//adds a process to list with void function(void) type and its process name
void processor::add(void (*f)(void), char* processName_)
{
	processList[processes] = f;
	processName[processes] = processName_;
	processes++;
}
//removes a processor from the list with given name
void processor::remove(char* processName_)
{	
		
}
bool processor::process(char * cmd)
{
	//linear search for the process and execute it
		bool isProcessed=false;		//flag 
		for(int i=0;i<processes;i++)
	{
			if(strcmp(processName[i],cmd)==0)
			{
				processList[i]();
				isProcessed=true;
			}
	}
	if(isProcessed==false)return 0;
	else return 1;
}

