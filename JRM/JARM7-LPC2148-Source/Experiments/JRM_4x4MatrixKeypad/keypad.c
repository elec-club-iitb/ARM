#include <LPC214x.H>                       /* LPC21xx definitions */
#include "keypad.h"

unsigned char keyPadMatrix [4][4]= {
                          {1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 16}
                        };


unsigned char decode_keypad(unsigned int  row_mask,unsigned int  col_mask);

/**
********************************************************************************************
  Function Name :	key_init()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void keypad_init()
{
  KEYPAD_DATA_DIR &= ~(ROW_MASK | COL_MASK);      
  KEYPAD_DATA_DIR |= COL_MASK;                    //make Rows as i/p and cols are 0/p
}

/**
********************************************************************************************
  Function Name :	key_init()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
unsigned char read_key()
{
  unsigned int  row=0,col=0,i;
  unsigned char key = KEY_NOT_PRESSED;
  
  KEYPAD_DATA_DIR &= ~(ROW_MASK);     
  KEYPAD_DATA_DIR |= COL_MASK;                   //make Rows as i/p and cols are o/p
  row=ROW_MASK&KEYPAD_DATA;                          //read rows
 
  
  KEYPAD_DATA_DIR &= ~(COL_MASK);	
  KEYPAD_DATA_DIR |= ROW_MASK;                   //make Rows as 0/p and cols are i/p
   for(i=0;i<5000;i++);
   col=COL_MASK&KEYPAD_DATA;                          //read cols
	
  KEYPAD_DATA_DIR &= ~(ROW_MASK | COL_MASK);		
  KEYPAD_DATA_DIR |= COL_MASK;					//make Rows as i/p and cols are 0/p

  key = decode_keypad(row,col);                        //decode the entered key

  return key;
}

/**
********************************************************************************************
  Function Name :	get_row()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
unsigned char get_row(unsigned int  row_mask)
{
  unsigned char ret_val = KEY_NOT_PRESSED;
  
  switch(row_mask ^ ROW_MASK)
  {
    case ROW0:
         ret_val = 0;
         break;
         
    case ROW1:
         ret_val = 1;
         break;

    case ROW2:
         ret_val = 2;
         break;

    case ROW3:
         ret_val = 3;
         break;				 
       
    default:
         break;
  }
	
  return(ret_val);
}
/**
********************************************************************************************
  Function Name :	get_col()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
unsigned char get_col(unsigned int  col_mask)
{
  unsigned char ret_val = KEY_NOT_PRESSED;
  
  switch(col_mask ^ COL_MASK)
  {
    case COL0:
         ret_val = 0;
         break;
         
    case COL1:
         ret_val = 1;
         break;

    case COL2:
         ret_val = 2;
         break;
         
    case COL3:
         ret_val = 3;
         break;
       
    default:
         break;
  }
	
  return(ret_val);
}

/**
********************************************************************************************
  Function Name :	decode_keypad()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
unsigned char decode_keypad(unsigned int  row_mask,unsigned int  col_mask)
{
  unsigned char row=0,col=0,key=KEY_NOT_PRESSED;
  
  row=get_row(row_mask);
  col=get_col(col_mask);

  if(row!=KEY_NOT_PRESSED && col!=KEY_NOT_PRESSED)
  key=keyPadMatrix[row][col];
  else
  key=KEY_NOT_PRESSED;

  return(key);
}


