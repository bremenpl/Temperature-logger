/*
 * data_collect.h
 *
 * Created: 2014-03-26 18:39:29
 *  Author: Lukasz
 */ 


#ifndef DATA_COLLECT_H_
#define DATA_COLLECT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>

#define BTN1_vect					INT2_vect
#define BTN2_vect					INT3_vect
#define BTN3_vect					INT6_vect

#define BTN1_INT					INT2
#define BTN2_INT					INT3
#define BTN3_INT					INT6

#define BTN1_INTF					INTF2
#define BTN2_INTF					INTF3
#define BTN3_INTF					INTF6

#define HOURS_PER_DAY				24
#define MEASURES_PER_HOUR			6
#define DATA_STORE_INTERVAL_MIN		10
#define CELL_TAGGED_MASK			1

extern uint16_t g_timeArray[HOURS_PER_DAY][MEASURES_PER_HOUR];
extern int8_t g_specificHour;
extern int8_t g_specificMinute;
extern bool g_startFastTimeSwap;

void Buttons_Init();
void TimeCheckTimer0_Init();
void TimerPushTimeout1_Init();
void TimerDebounce3_Init();

void IncrementTimeCell();
void DecrementTimeCell();



#endif /* DATA_COLLECT_H_ */