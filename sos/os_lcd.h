#ifndef __RRM_LCD_N5110_H_
#define __RRM_LCD_N5110_H_

#include "rrm_config.h"

//screen size
#define LCD_N5110_WIDTH 	84
#define LCD_N5110_HEIGHT 	48
#define LCD_N5110_CWIDTH	6
#define LCD_N5110_CHEIGT	8

#define LCD_N5110_CMD		0
#define LCD_N5110_DATA		1

#define LCD_N5110_PORT		PORTB
#define LCD_N5110_DDR		DDRB

#define LCD_N5110_CE		PB0
#define LCD_N5110_RST		PB1
#define LCD_N5110_DC		PB2
#define LCD_N5110_DIN		PB3
#define LCD_N5110_CLK		PB4


//portX, ce, rst, dc, din, clk
extern void lcd_n5110_init(void);
//contrast
//extern void lcd_n5110_contrast(uint8_t);
extern void lcd_n5110_clear(void);
//line, x, y
extern void lcd_n5110_clear_area(uint8_t, uint8_t, uint8_t);
//line
extern void lcd_n5110_clear_line(uint8_t);
//x, y
extern void lcd_n5110_goto_xy(uint8_t, uint8_t);
//x, y
extern void lcd_n5110_goto_xy_exact(uint8_t, uint8_t);
//char
extern void lcd_n5110_char(char);
//string
extern void lcd_n5110_string(char *);
extern void lcd_n5110_format_string(char *, ...);
//data, cmd (T/F)
extern void lcd_n5110_send(uint8_t, uint8_t);
//base addr
extern void lcd_n5110_base_addr(uint16_t);
//char
//extern void lcd_n5110_col(char);
//extern void lcd_n5110_pixelback(void);
//x, y, color
extern void lcd_n5110_drawpixel(uint8_t, uint8_t, int);
extern void lcd_n5110_drawimage(const unsigned char *);

#endif //__RRM_LCD_N5110_H_
