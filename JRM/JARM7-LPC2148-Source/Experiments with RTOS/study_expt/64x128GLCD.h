#ifndef  _64x128CLCD_H_
#define  _64x128CLCD_H_

#define LCD_DATA_DIR		FIO0DIR
#define LCD_DATA_SET		FIO0SET
#define LCD_DATA_CLR		FIO0CLR

#define LCD_CTRL_DIR		FIO0DIR
#define LCD_CTRL_SET    FIO0SET
#define LCD_CTRL_CLR    FIO0CLR

#define LCD_D0 BIT15
#define LCD_D1 BIT16
#define LCD_D2 BIT17
#define LCD_D3 BIT18
#define LCD_D4 BIT19
#define LCD_D5 BIT20
#define LCD_D6 BIT21
#define LCD_D7 BIT22

#define LCDRW	 BIT12
#define LCDRS	 BIT13
#define LCDCS1B BIT5
#define LCDRST BIT6
#define LCDEN BIT11

#define GLCD_DATA_MASK (LCD_D0 | LCD_D1 | LCD_D2 | LCD_D3 | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)
#define LCD_CTRL_MASK (LCDRW | LCDRS | LCDCS1B | LCDRST)

#define PAGE1	0xB0
#define COL1	1
#define		HIGH	1		
#define		LOW		0

void LCD_INIT(void);
void LCD_WRITE_CMD(unsigned char cmd);
unsigned char LCD_READ_CMD();
void LCD_WRITE_DATA(unsigned char data);
void LCD_SET_PAGE(unsigned char page,unsigned char col);
void LCD_CLEAR(void);

#endif //_64x128CLCD_H_

