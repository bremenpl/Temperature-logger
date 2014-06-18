/*
 * data_collect.c
 *
 * Created: 2014-03-26 18:39:16
 *  Author: Lukasz
 */ 

#include "data_collect.h"
#include "hardware.h"
#include "buf_lcd.h"
#include "warstwy.h"

#define TIMER1ON()			(TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10))
#define TIMER1OFF()			(TCCR1B = 0)
#define TIMER1RESET() \		
{\
TCCR1B = 0;\
TCNT1 = 0;\
TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);\
}

#define TIMER3ON()			(TCCR3B = _BV(WGM32) | _BV(CS32) | _BV(CS30))
#define TIMER3OFF()			(TCCR3B = 0)

uint16_t g_timeArray[HOURS_PER_DAY][MEASURES_PER_HOUR];
int8_t g_specificHour = 0;
int8_t g_specificMinute = 0;
bool g_startFastTimeSwap = false;

uint8_t timer1Counter = 0;

void Buttons_Init()
{
	// config as inputs
	BTN1_DDR &= ~_BV(BTN1_P);
	BTN2_DDR &= ~_BV(BTN2_P);
	BTN3_DDR &= ~_BV(BTN3_P);
	
	EICRA |= _BV(ISC21) | _BV(ISC31);
	EICRB |= _BV(ISC61);
	EIFR  |= _BV(BTN1_INTF) | _BV(BTN2_INTF) | _BV(BTN3_INTF);
	EIMSK |= _BV(BTN1_INT) | _BV(BTN2_INT) | _BV(BTN3_INT);
}

void TimeCheckTimer0_Init()
{
	// set timer0 to CTC 
	TCCR0A = _BV(WGM10); // set ctc
	TCCR0B = _BV(CS00) | _BV(CS02); // prescaller = 1024
	OCR0A = 155; // bit more than 0.01 s 
	TCNT0 = 0;
	TIFR0 |= _BV(OCF0A); // clear interrupt flag
	TIMSK0 |= _BV(OCIE0A); // enable ctc interrupt
}

ISR(TIMER0_COMPA_vect)
{
	SubstractTimeMeasure_Flag();
	
	if(++ms10_cnt>99)
	ms10_cnt=0;
	if(++s1_cnt>59)
	s1_cnt=0;
}

ISR(BTN1_vect)
{
	EIMSK &= ~_BV(BTN1_INT);
	
	DecrementTimeCell();
	
	g_activeLayer = SPECIFIC_TIME_MASK;
	TIMER3ON();
}

ISR(BTN2_vect)
{
	EIMSK &= ~_BV(BTN2_INT);
	g_activeLayer = LOWEST_HIGHEST_TEMP_MASK;
	
	timer1Counter = 0;
	TIMER1RESET();
}

ISR(BTN3_vect)
{
	EIMSK &= ~_BV(BTN3_INT);
	
	IncrementTimeCell();
	
	g_activeLayer = SPECIFIC_TIME_MASK;
	TIMER3ON();
}

void TimerPushTimeout1_Init()
{
	TIMER1OFF();
	OCR1A = 46874; // 3 s, prescaller 1024
	TCNT1 = 0;
	TIFR1 = _BV(OCF1A);
	TIMSK1 = _BV(OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	if (timer1Counter >= 1) // every 8 seconds
	{
		timer1Counter = 0;
		g_activeLayer = DATE_AND_TIME_MASK;
		
		EIFR  |= _BV(BTN2_INTF);
		EIMSK |= _BV(BTN2_INT);
		
		TIMER1OFF();
	}
	else
	{
		timer1Counter++;
		g_startFastTimeSwap = true;
	}
}

void TimerDebounce3_Init()
{
	TIMER3OFF();
	OCR3A = 468; // 30 ms, prescaller 1024
	TCNT3 = 0;
	TIFR3 = _BV(OCF3A);
	TIMSK3 = _BV(OCIE3A);
}

ISR(TIMER3_COMPA_vect)
{
	EIFR  |= _BV(BTN1_INTF) | _BV(BTN3_INTF);
	EIMSK |= _BV(BTN1_INT) | _BV(BTN3_INT);
	
	EIFR  |= _BV(BTN2_INTF);
	EIMSK |= _BV(BTN2_INT);
	
	TIMER3OFF();
}

void IncrementTimeCell()
{
	if (g_specificMinute >= ((MEASURES_PER_HOUR - 1) * 10))
	{
		g_specificMinute = 0;
		
		if (g_specificHour >= (HOURS_PER_DAY - 1))
		{
			g_specificHour = 0;
		}
		else
		{
			g_specificHour++;
		}
	}
	else
	{
		g_specificMinute += 10;
	}
	
	timer1Counter = 0;
	TIMER1RESET();
}

void DecrementTimeCell()
{
	if (0 == g_specificMinute)
	{
		g_specificMinute = (MEASURES_PER_HOUR - 1) * 10;
		
		if (0 == g_specificHour)
		{
			g_specificHour = HOURS_PER_DAY - 1;
		}
		else
		{
			g_specificHour--;
		}
	}
	else
	{
		g_specificMinute -= 10;
	}
	
	timer1Counter = 0;
	TIMER1RESET();
}

