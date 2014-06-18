/*
 * buf_lcd.h
 *
 *  Created on: 23-02-2012
 *      Author: Miros³aw Kardaœ
 */

#ifndef BUF_LCD_H_
#define BUF_LCD_H_


#define ROWS						2
#define COLS						16

#define LCD_REFRESH_MS				20
#define MAX_BULLETS					4
#define TRANSPARENT_CHAR			'^'

typedef struct {
	int8_t y;
	int8_t x;
	uint8_t width;
	uint8_t height;
	uint8_t visible;
	char buf[ROWS*COLS];
	void (*EVENT)(void);
} TWIN_t;

#define AT(y,x) ((y*COLS)+x)

extern uint8_t buf_y;		// zmienne przechowuj¹ce pozycjê kursora
extern uint8_t buf_x;

extern char hd_buf[ROWS*COLS];
extern volatile uint8_t ms10_cnt;
extern volatile uint8_t s1_cnt;
extern char * active_buf;

void BARREL_EVENT(uint8_t all);
void buf_lcd_init(void);
int8_t create_obj(TWIN_t * bf, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t visible, void (*event)(void));
void free_obj(uint8_t handle);

void buf_cls(void);
void buf_locate(uint8_t y, uint8_t x);
void buf_str(char * s);
void buf_str_ex(char *s, uint8_t len);
void buf_str_P(char * s);
void buf_hex(int val);
void buf_int(int val);

void buf_char(char * wbf, char z);
void buf_fill(char znak, uint8_t len);



#endif /* BUF_LCD_H_ */
