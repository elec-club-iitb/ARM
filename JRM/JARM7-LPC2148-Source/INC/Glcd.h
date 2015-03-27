#ifndef __GLCD_H
#define __GLCD_H


extern void Glcd_Init(	volatile unsigned long *ctrl_port,
								volatile unsigned long *data_port,
								unsigned char cs1_pin,
								unsigned char cs2_pin,
								unsigned char rs_pin,
								unsigned char rw_pin,
								unsigned char rst_pin,
								unsigned char en_pin,
								unsigned char D0_pin);

extern void Glcd_Set_Side(unsigned char x_pos);
extern void Glcd_Set_Page(unsigned char page);
extern void Glcd_Set_X(unsigned long x_pos);
extern unsigned char Glcd_Read_Data(void);
extern void Glcd_Write_Data(unsigned char ddata);

extern void Glcd_Fill(unsigned char pattern);
extern void GLCD_Dot(unsigned long x_pos, unsigned long y_pos, unsigned char color);
extern void Glcd_Line(	long x_start,
								long y_start,
								long x_end,
								long y_end,
								unsigned char color);
extern void Glcd_V_Line(	long y_start,
									long y_end,
									long x_pos,
									unsigned char color);
extern void Glcd_H_Line(	long x_start,
									long x_end,
									long y_pos,
									unsigned short color);
extern void Glcd_Rectangle(long x_upper_left,
										long y_upper_left,
										long x_bottom_right,
										long y_bottom_right,
										unsigned char color);
extern void Glcd_Box(long x_upper_left,
							long y_upper_left,
							long x_bottom_right,
							long y_bottom_right,
							unsigned char color);
extern void Glcd_Circle(	long x_center,
									long y_center,
									long radius,
									unsigned char color);

extern void Glcd_Set_Font(	const char *activeFont,
										unsigned char aFontWidth,
										unsigned char aFontHeight,
										unsigned long aFontOffs);
extern void Glcd_Write_Char(unsigned char chr,
                     unsigned long x_pos,
                     unsigned char page_num,
                     unsigned char color);
extern void Glcd_Write_Text(	char *text,
											unsigned long x_pos,
											unsigned char page_num,
											unsigned char color);

extern void Glcd_Image(const unsigned char *image);



#endif
