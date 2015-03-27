#include "utils.h"
#include "64x128GLCD.h"
#include "lcd_app.h"
#include "includes.h"

unsigned char frame_buf[NUM_OF_COL][NUM_OF_PAGES];

enum BRUSH_TYPE
{
	BRUSH_OFF,
	BRUSH_ON,
 	BRUSH_XOR
};

/**
*******************************************************************************
  Function Name : clear_frame_buf()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
void clear_frame_buf(void)
{
  unsigned char page_num = 0, col_num = 0;
  
  for(page_num = 0; page_num < MAX_NUM_OF_PAGES; page_num++)
  	for(col_num = 0; col_num < NUM_OF_COL; col_num++)
		frame_buf[col_num][page_num] = 0;
}
/**
*******************************************************************************
  Function Name : lcd_goto_xy()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
void lcd_goto_xy(unsigned char x_address, unsigned char y_address)
{
  unsigned char page_num = x_address/NUM_OF_PAGES;

  LCD_SET_PAGE(PAGE1 + page_num, y_address);
}

/**
*******************************************************************************
  Function Name : put_pixel()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
void put_pixel(unsigned short int px, unsigned short int py, unsigned char brush)
{
  unsigned char data = 0;
  unsigned short int page_num = 0;
  
  if((px< NUM_OF_ROWS) && (py < NUM_OF_COL))
  {
    page_num = px / NUM_OF_PAGES;
    data = 1 << (px % 8);
        
    lcd_goto_xy((unsigned char)px,(unsigned char)py);
    
    switch(brush)
    {
      case BRUSH_ON:
        frame_buf[py][page_num] |= data;

        break;
        
      case BRUSH_OFF:
       frame_buf[py][page_num] &= ~data;
        break;
        
      case BRUSH_XOR:
        frame_buf[py][page_num] ^= data;
        break;
        
      default:
        break;
    }
	
  LCD_WRITE_DATA(frame_buf[py][page_num]);
  }
}


/**
*******************************************************************************
  Function Name : lcd_draw_line()

  Description :	 

  Input :	

  Output :	none

  Note : 
*******************************************************************************
*/
void lcd_draw_line(unsigned short int x1,unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int thickness)
{
  signed short int dx,dy,dxabs,dyabs,i,px,py,sdx,sdy,x,y;
  unsigned short int j = 0;
  
  if(thickness > MAX_THICKNESS)
  {
    thickness = MAX_THICKNESS;
  }
  dx = x2 - x1;
  dy = y2 - y1;
  
  sdx = SIGN(dx);
  sdy = SIGN(dy);
  
  dxabs = ABSOLUTE(dx);
  dyabs = ABSOLUTE(dy);
  
  x = 0; y = 0;
  
  px = x1;
  py = y1;
  
  if(dxabs >= dyabs)
  {
    for(i=0;i <=dxabs;i++)
    {
      y += dyabs;
      if(y >= dxabs)
      {
        y -= dxabs;
        py += sdy;
      }
      for(j = 0; j < thickness; j++)
      {
        put_pixel(px+j,py,BRUSH_ON);
      }
      px +=sdx;
    }
  }
  else
  {
    for(i=0; i<=dyabs;i++)
    {
      x += dxabs;
      if(x >= dyabs)
      {
        x -= dyabs;
        px += sdx;
      }
      for(j = 0; j < thickness; j++)
      {
      	put_pixel(px+j,py,BRUSH_ON);
      }
      py += sdy;
    }
  }
}

/**
*******************************************************************************
  Function Name : lcd_draw_circle()

  Description :	 

  Input :	

  Output :	none

  Note : Bresenham's Circle Algorithm 
         Taken from http://en.wikipedia.org/wiki/Bresenham's_line_algorithm 
*******************************************************************************
*/
void lcd_draw_circle(unsigned short int x0, unsigned short int y0, unsigned short int radius)
{
  signed int f = 1 - radius;
  unsigned short int ddF_x = 0;
  signed int ddF_y = -2 * radius;
  unsigned short int x = 0;
  unsigned short int y = radius;
  
  put_pixel(x0, y0 + radius,BRUSH_ON);
  put_pixel(x0, y0 - radius,BRUSH_ON);
  put_pixel(x0 + radius, y0,BRUSH_ON);
  put_pixel(x0 - radius, y0,BRUSH_ON);
  
  while(x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;
    put_pixel(x0 + x, y0 + y,BRUSH_ON);
    put_pixel(x0 - x, y0 + y,BRUSH_ON);
    put_pixel(x0 + x, y0 - y,BRUSH_ON);
    put_pixel(x0 - x, y0 - y,BRUSH_ON);
    put_pixel(x0 + y, y0 + x,BRUSH_ON);
    put_pixel(x0 - y, y0 + x,BRUSH_ON);
    put_pixel(x0 + y, y0 - x,BRUSH_ON);
    put_pixel(x0 - y, y0 - x,BRUSH_ON);
  }
}

/**
********************************************************************************************
	Function Name :	is_valid_ascii()

	Description :
	
	Input :	Void

	Output : Void

	Note :
**********************************************************************************************
*/
unsigned char is_valid_ascii(signed short int key)
{
  unsigned char retval = 0;
  
  if(key >= ' ' && key <= '~')
    retval = 1;

  return retval;
}

/**
********************************************************************************************
	Function Name :	lcd_display_char()

	Description :
	
	Input :	Void

	Output : Void

	Note :
**********************************************************************************************
*/
void lcd_display_char(unsigned char charecter)
{
  unsigned char width = 0, index = 0, data = 0;
  
  width = get_width_of_char(charecter);
  for(index = 0; index < width; index++)
  {
    data = get_data_from_data_table(charecter, index);
    LCD_WRITE_DATA(data);
  }
}

/**
********************************************************************************************
	Function Name :	lcd_display_string()

	Description :
	
	Input :	Void

	Output : Void

	Note :
**********************************************************************************************
*/
void lcd_display_string(unsigned char *str)
{
  if(str == 0)
    return;
    
  while(*str != 0)
  {
    lcd_display_char(*str);
    str++;
  }
}
/**
*****************************************************************************
	Function Name : init_glcd_ports()

	Description   :

	Input         : Void 

	Output        : None

	Note          :
******************************************************************************
*/
void init_glcd_ports(void)
{
  LCD_DATA_DIR |= GLCD_DATA_MASK;
  LCD_CTRL_DIR |= LCD_CTRL_MASK;
}

void init_xy_axis(void)
{
	LCD_SET_PAGE(PAGE1 + 4 , COL1);
	lcd_display_string("adc");
	LCD_SET_PAGE(PAGE1 + 7 , COL1);
	lcd_display_string("				         time");
	
	lcd_draw_line(INITIAL_X_AXIS_POS, INITIAL_Y_AXIS_POS, 0, INITIAL_Y_AXIS_POS, 1);
	lcd_draw_line(INITIAL_X_AXIS_POS, INITIAL_Y_AXIS_POS, INITIAL_X_AXIS_POS, 127, 1);
}

