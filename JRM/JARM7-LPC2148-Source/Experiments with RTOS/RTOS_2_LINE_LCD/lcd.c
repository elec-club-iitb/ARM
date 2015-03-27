#include <LPC214x.H>                       /* LPC214x definitions */
#include "lcd.h"

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

/**
********************************************************************************************
  Function Name :	wait_lcd()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void wait_lcd( void )
{
  LCD_CTRL_CLR |=  LCDRS;	
  LCD_CTRL_SET |=	LCDEN;
  LCD_CTRL_SET |=  LCDRW ;  
  
  delay(10);
  
  LCD_CTRL_CLR |= LCDEN ;  
  LCD_CTRL_CLR |= LCDRW;

  LCD_DATA_DIR |= LCD_DATA_MASK;
}

/**
********************************************************************************************
  Function Name :	lcd_command_write()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_command_write( unsigned char command )
{
  unsigned char temp=0;
  unsigned int temp1=0;

  temp=command;
  temp=(temp>>4)&0x0F;
  temp1=(temp<<19)&LCD_DATA_MASK;

  LCD_CTRL_CLR |= LCDRS;
  LCD_CTRL_SET |= LCDEN;  
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET = temp1;
  LCD_CTRL_CLR |= LCDEN;  

  temp=command;
  temp&=0x0F;
  temp1=(temp<<19)&LCD_DATA_MASK;

  LCD_CTRL_CLR |= LCDRS;
  LCD_CTRL_SET |= LCDEN;  
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET |= temp1;
  delay(10000);	
  LCD_CTRL_CLR |= LCDEN;  
  wait_lcd();
}
/**
********************************************************************************************
  Function Name :	set_lcd_port_output()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void set_lcd_port_output( void )
{
  LCD_CTRL_DIR |= ( LCDEN );  
  LCD_CTRL_DIR |= ( LCDRS | LCDRW );
  LCD_CTRL_CLR |= ( LCDEN );	
  LCD_CTRL_CLR |= ( LCDRS | LCDRW );	
  LCD_DATA_DIR |= LCD_DATA_MASK;
}
/* *
********************************************************************************************
  Function Name :	lcd_clear()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_clear( void)
{
  lcd_command_write( 0x01 );
}

/* *
********************************************************************************************
  Function Name :	lcd_line_clear()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_line_clear(unsigned char line)
{
  char temp_buf[MAX_CHAR_IN_ONE_LINE];
  int i=0;

  if(line > 1)
    return;

  for(i=0; i<MAX_CHAR_IN_ONE_LINE; i++)
    temp_buf[i] = ' ';

  lcd_putstring( line, temp_buf );
}

/**
********************************************************************************************
  Function Name :	lcd_gotoxy()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
int lcd_gotoxy( unsigned int x, unsigned int y)
{
  int retval = 0;
  
  if( (x > 1) && (y > 15) )
  {
    retval = -1;
  } else {
  if( x == 0 )
  {
    lcd_command_write( 0x80 + y );		/* command - position cursor at 0x00 (0x80 + 0x00 ) */
  } else if( x==1 ){
    lcd_command_write( 0xC0 + y );		/* command - position cursor at 0x40 (0x80 + 0x00 ) */
    }
   }
   return retval;
}

/**
********************************************************************************************
  Function Name :	lcd_data_write()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_data_write( unsigned char data )
{
  unsigned char temp=0;
  unsigned int temp1=0;

  temp=data;
  temp=(temp>>4)&0x0F;
  temp1=(temp<<19)&LCD_DATA_MASK;

  LCD_CTRL_SET |= LCDEN;  
  LCD_CTRL_SET |= LCDRS;
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET |= temp1;
  LCD_CTRL_CLR |= LCDEN;
  

  temp=data;
  temp&=0x0F;
  temp1=(temp<<19)&LCD_DATA_MASK;

  LCD_CTRL_SET |= LCDEN;  
  LCD_CTRL_SET |= LCDRS;
  LCD_DATA_CLR |= LCD_DATA_MASK;
  LCD_DATA_SET |= temp1;
  LCD_CTRL_CLR |= LCDEN;
  
  wait_lcd();
}
/**
********************************************************************************************
  Function Name :	lcd_putchar()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_putchar( int c )
{
  lcd_data_write( c );
}

/**
********************************************************************************************
  Function Name :	lcd_putstring()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void lcd_putstring( unsigned char line, char *string )
{
  unsigned char len = MAX_CHAR_IN_ONE_LINE;

  lcd_gotoxy( line, 0 );
  while(*string != '\0' && len--)
  {
    lcd_putchar( *string );
    string++;
  }
}

/**
********************************************************************************************
  Function Name :	init_lcd()
  
  Description   :	
  
  Input         :	
  
  Output        :	Void
  
  Note          :
********************************************************************************************
*/
void init_lcd( void )
{
  set_lcd_port_output();
  delay(100*100);
  delay(100*100);
	
  lcd_command_write(0x28);     /*   4-bit interface, two line, 5X7 dots.        */
  lcd_clear() ;                /*   LCD clear                                   */
  lcd_command_write(0x02);     /*   cursor home                                 */
  lcd_command_write(0x06);     /*   cursor move direction                       */
  lcd_command_write(0x0C) ;    /*   display on      */
  lcd_gotoxy(0, 0);
  lcd_clear();	
  lcd_putstring(0,"     N G X   ");
  lcd_putstring(1,"  TECHNOLOGIES ");
}
