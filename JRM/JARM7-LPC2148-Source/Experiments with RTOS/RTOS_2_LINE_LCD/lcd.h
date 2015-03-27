#ifndef _LCD_H
#define _LCD_H

#define MAX_CHAR_IN_ONE_LINE 16

#define LCD_BACK_LIGHT_DIR IODIR1
#define LCD_BACK_LIGHT_SET IOSET1
#define LCD_BACK_LIGHT_CLR IOCLR1

#define LCD_DATA_DIR		IODIR0
#define LCD_DATA_SET		IOSET0
#define LCD_DATA_CLR		IOCLR0

#define LCD_BUSY_FLAG_IO_PIN IOPIN0

#define LCD_CTRL_DIR		    IODIR0
#define LCD_CTRL_SET            IOSET0
#define LCD_CTRL_CLR            IOCLR0

#define LCDEN_CTRL_DIR		      IODIR1
#define LCDEN_CTRL_SET            IOSET1
#define LCDEN_CTRL_CLR            IOCLR1

#define LCDRS	                (1 << 13)
#define LCDRW	                (1 << 12)
#define LCDEN	                (1 << 10)

#define LCD_D4 (1 << 19)
#define LCD_D5 (1 << 20)
#define LCD_D6 (1 << 21)
#define LCD_D7 (1 << 22)

#define LCD_DATA_MASK          (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)
#define LCD_BUSY_FLAG           LCD_D7

#define LCD_CONTROL_MASK        (LCDRS | LCDRW | LCDEN)

enum ROW_NUMBERS
{
  LINE1,
  LINE2	
};

void init_lcd(void);
void lcd_putstring(unsigned char line, char *string);
void lcd_clear(void);
int lcd_gotoxy(unsigned int x, unsigned int y);
void lcd_putchar(int c);

#endif
