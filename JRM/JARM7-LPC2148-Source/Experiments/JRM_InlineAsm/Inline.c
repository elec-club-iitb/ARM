#include <stdio.h>                /* prototype declarations for I/O functions */

#define OPERAND1  100
#define OPERAND2  25

extern void init_serial (void);


int assembly_add (int param1, int param2)  {
  int	output;

  __asm  {
	ADD output, param1, param2 
  }
  return (output); //  param1 + param2 + param2
}

int assembly_sub (int param1, int param2)
{
	int output;

	__asm  	{

	SUB output, param1, param2
	}
	return (output);
}

int assembly_mul (int param1, int param2)
{
	int output;

	__asm  	{

	MUL output, param1, param2
	}
	return (output);
}

int assembly_div (int param1, int param2)
{
	int output = 0;

	__asm  	{

	loop:
		SUB param1, param1, param2
		ADD output, output, 1
		CMP param1, param2
		BHS loop
	}
	return (output);
}

int main (void) 
{
  int	Add, Sub, Mul, Div;
 
  init_serial();	                  // init serial port

  printf("Inline-Assembly Example\n"); 

  Add 		=	assembly_add(OPERAND1, OPERAND2);  // Add 'operand1' and 'operand2' and store the result in 'Add'
  Sub 		=	assembly_sub(OPERAND1, OPERAND2);  // Subtract 'operand1' and 'operand2' and store the result in 'Sub'
  Mul		=	assembly_mul(OPERAND1, OPERAND2);  // Multiply 'operand1' and 'operand2' and store the result in 'Mul'
  Div		=	assembly_div(OPERAND1, OPERAND2);  // Divide 'operand1' by 'operand2' and store the result in 'Div'

  printf(" assembly_add (OPERAND1, OPERAND2) : Add 	= %d\n", Add); // display the result on the hyperterminal through serial port
  printf(" assembly_sub (OPERAND1, OPERAND2) : Sub 	= %d\n", Sub);
  printf(" assembly_mul (OPERAND1, OPERAND2) : Mul 	= %d\n", Mul);
  printf(" assembly_div (OPERAND1, OPERAND2) : Div 	= %d\n", Div);
  printf("End Inline-Assembly Example.\n");

  while (1) {                          /* An embedded program does not stop and       */
    ;  /* ... */                       /* never returns. We use an endless loop.      */
  }                                    /* Replace the dots (...) with your own code.  */

}
