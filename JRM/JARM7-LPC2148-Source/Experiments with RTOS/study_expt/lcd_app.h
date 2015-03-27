#ifndef _LCD_APP_H
#define _LCD_APP_H

#define MAX_THICKNESS 4

#define NUM_OF_ROWS 64
#define NUM_OF_COL 128
#define NUM_OF_PAGES 8

#define MAX_NUM_OF_PAGES 8

#define INITIAL_Y_AXIS_POS 18
#define INITIAL_X_AXIS_POS 55

void put_pixel(unsigned short int px, unsigned short int py, unsigned char brush);
void init_glcd_ports(void);
void init_xy_axis(void);
void clear_frame_buf(void);
#endif

