//UART library header file
//Registers  : U0RBR
//Uart library 
//
#define EVEN_PARITY 1
#define ODD_PARITY 0

class uart0 
{
	unsigned long baud;	//store actual baud rate
	unsigned int stopBits;
	unsigned int dataWidth;
	int parity;
	unsigned long pclk;
			void callSetBaud();
	public : 
		uart0(unsigned long pclk,
					unsigned long _baud=9600,		//baud rate
					unsigned int _dataWidth=8,	//5 to 8 bit character length
					unsigned int _stopBits=1,		//1 or 2
					int parity=0);		//0=even parity
		unsigned long getBaud();		//getter function
		void setBaud(unsigned long baud);	//set baud //quickly apply changes
		
		void write(char data); //write data to fifo
		char read(void); //read data from fifo //or wait until data is recieved 
		void printString(char*);
		
};
