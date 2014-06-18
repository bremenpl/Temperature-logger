/*
 * buf_lcd.c
 *
 *  Created on: 23-02-2012
 *      Author: Miros³aw Kardaœ
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>

#include "buf_lcd.h"
#include "lcd44780.h"

uint8_t buf_y;		// zmienne przechowuj¹ce pozycjê kursora
uint8_t buf_x;

char hd_buf[ROWS*COLS];		// g³ówny bufor LCD

char * active_buf = hd_buf;	// wskaŸnik aktywnego bufora


TWIN_t * barrel[MAX_BULLETS];


volatile uint8_t ms10_cnt;	// zmienna na potrzeby timerów programowych
volatile uint8_t s1_cnt;




//******** inicjalizacja mechanizmu buforowania LCD
void buf_lcd_init(void) {
	lcd_init();						// inicjalizacja LCD

	uint8_t i;
	for(i=0; i<MAX_BULLETS; i++) 
		barrel[i]=0;

	buf_cls();
}


void copy_buf(TWIN_t * w) {
	int8_t x,y;
	uint8_t ax, ay;
	active_buf = hd_buf;

	for(y=w->y, ay=0; y<w->y+w->height; y++, ay++) {
		buf_locate(y, w->x);
		for(x=w->x, ax=0; x<w->x+w->width; x++, ax++) {
			if(x<COLS && y<ROWS && x>=0 && y>=0) {
				if(w->buf[AT(ay,ax)] != TRANSPARENT_CHAR) buf_char(hd_buf, w->buf[AT(ay,ax)]);
				else buf_x++;
			}
		}
	}
}

//******************************************************************
//     Zdarzenie EVENT odpowiedzialne za wyœwietlanie na LCD
//******************************************************************
void BARREL_EVENT(uint8_t all) 
{
	volatile uint8_t y, x, idx=0;
	static uint8_t lms10=255;

	if( lms10 != ms10_cnt ) 
	{	// co 10ms
		if(all) 
		{				// jeœli aktywna obs³uga warstw oraz ich zdarzeñ
			while(idx < MAX_BULLETS) 
			{	// sprawdŸ po kolei wszystkie bufory/warstwy
				if( barrel[idx] ) 
				{	
					// jeœli warstwa uwzglêdniona w tablicy warstw
 					if(barrel[idx]->EVENT) 
 						barrel[idx]->EVENT();	// jeœli przydzielone zdarzenie - wykonaj je
					if( barrel[idx]->visible ) 
 						copy_buf(barrel[idx]); // jeœli warstwa ma byæ widoczna - poka¿ j¹
				}
				idx++;	// zwiêksz licznik warstw
			}
		}

		// wyœwietl na ekranie LCD zawartoœæ bufora RAM
		if(!(ms10_cnt % (LCD_REFRESH_MS  /10))) 
		{
			for(y=0;y<ROWS;y++) 
			{
				lcd_locate(y,0);
				for(x=0;x<COLS;x++) 
					lcd_char(hd_buf[AT(y,x)]);
			}
		}
		lms10 = ms10_cnt;
	}
}

int8_t create_obj(TWIN_t * bf, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t visible, void (*event)(void)) {
	uint8_t i;
	for(i=0;i<MAX_BULLETS;i++) {
		if(!barrel[i]) {
			bf->x=x;
			bf->y=y;
			bf->width=width;
			bf->height=height;
			bf->EVENT=event;
			bf->visible=visible;
			barrel[i]=bf;
			active_buf=bf->buf;
			buf_cls();
			break;
		}
	}
	if(MAX_BULLETS==i) i=-1;
	return i;
}

void free_obj(uint8_t handle) {
	barrel[handle]=NULL;
}

//*********************************************************************************************
//****************************************** funkcje narzêdziowe do wyœwietlania **************

// wyczyszczenie aktywnego bufora
void buf_cls(void) {
	memset(active_buf, ' ', ROWS*COLS);
	buf_y=0; buf_x=0;
}


// ustawienie kursora ekranu/bufora
void buf_locate(uint8_t y, uint8_t x) {
	if(y<ROWS) buf_y = y; else buf_y = 0;
	if(x<COLS) buf_x = x; else buf_x = 0;
}

// wype³nienie ekranu/bufora jednym znakiem w iloœci len
void buf_fill(char znak, uint8_t len) {
	uint8_t i;
	for(i=0;i<len;i++) buf_char(active_buf, znak);
}

// wys³anie pojedynczego znaku do wskazanego bufora
void buf_char(char * wbf, char z) {

	if(buf_y>=0 && buf_y<ROWS && buf_x>=0 && buf_x<COLS) {

		wbf[AT(buf_y,buf_x)] = z;
		buf_x++;
	}
}

// wys³anie znaków z bufora o d³ugoœci len
void buf_str_ex(char *s, uint8_t len) {
	while(len--) buf_char(active_buf, *s++);

}

// wys³anie stringa z pamiêci RAM
void buf_str(char * s) {
	while( *s ) buf_char(active_buf, *s++);
}

// wys³anie stringa z pamiêci FLASH
void buf_str_P(char * s) {
	char c;
	while( (c=pgm_read_byte(s++)) ) buf_char(active_buf, c);
}

// wys³anie liczby HEX
void buf_hex(int val) {
	char bufor[17];
	buf_str( itoa(val, bufor, 16) );
}

// wys³anie liczzby dziesiêtnej
void buf_int(int val) {
	char bufor[17];
	buf_str( itoa(val, bufor, 10) );
}


