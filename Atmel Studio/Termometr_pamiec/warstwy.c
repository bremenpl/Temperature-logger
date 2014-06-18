/*
 * warstwy.c
 *
 *  Created on: 28-02-2012
 *      Author: Miros³aw Kardaœ
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "lcd44780.h"
#include "buf_lcd.h"
#include "warstwy.h"
#include "i2c_twi.h"
#include "ds18b20.h"
#include "hardware.h"

#define INVALID_CELL		0xFF
#define HALF_MASK			0x0008
#define CELCIUS_SIGN		0xDF

typedef char * string;

string daysOfWeek[7] =
{
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun"
};


// podrêczne wspó³rzêdne do przesuwania warstwy alarm_layer
int8_t w1y, w1x;

// zmienne globalne - warstwy stworzone na sta³e w programie
TWIN_t g_dateAndTime_layer;
TWIN_t g_lowestAndHighestTemp_layer;
TWIN_t g_specificTime_layer;

uint8_t g_activeLayer;

void CheckCurrentVisibleLayer()
{
	g_dateAndTime_layer.visible = g_activeLayer & DATE_AND_TIME_MASK;
	g_lowestAndHighestTemp_layer.visible = g_activeLayer & LOWEST_HIGHEST_TEMP_MASK;
	g_specificTime_layer.visible = g_activeLayer & SPECIFIC_TIME_MASK;
}

//******************** WARSTWA 1 ********************************
void DateDisplayWindow_Event()
{
	char slotString[17];
	int16_t temperature = g_ds18b20TempValue[0] | (g_ds18b20TempValue[1] << 8);
	char half = '0';
	active_buf = g_dateAndTime_layer.buf;
	
	if ((temperature & HALF_MASK) != 0)
	{
		half = '5';
	}
	
	buf_cls();
	buf_locate(0,0);
	sprintf(slotString,"%s     %02i/%02i/%02i", daysOfWeek[g_date.day - 1], g_date.date, g_date.month, g_date.year);
	buf_str(slotString);
	buf_locate(1,0);
	
	if (temperature >= 0)
	{
		sprintf(slotString,"%02i.%c%cC  %02i:%02i:%02i",(temperature >> 4), half, CELCIUS_SIGN,  g_time.hour, g_time.minute, g_time.second);
	}
	else
	{
		sprintf(slotString,"%02i.%c%cC %02i:%02i:%02i",(temperature >> 4), half, CELCIUS_SIGN, g_time.hour, g_time.minute, g_time.second);
	}
	buf_str(slotString);
}

//******************** WARSTWA 2 ********************************
void LowestHighestTempWindow_Event()
{
	char slotString[17];
	char half = '0';
	
	volatile uint8_t hour = 0;
	volatile uint8_t minuteDecade = 0;
	 
	volatile uint8_t lowestTempOfTheDayHour = INVALID_CELL;
	volatile uint8_t lowestTempOfTheDayMinuteDecade = INVALID_CELL;
	
	volatile uint8_t highestTempOfTheDayHour = INVALID_CELL;
	volatile uint8_t highestTempOfTheDayMinuteDecade = INVALID_CELL;
	
	active_buf = g_lowestAndHighestTemp_layer.buf;

	for (hour = 0; hour < HOURS_PER_DAY; hour++)
	{
		for (minuteDecade = 0; minuteDecade < MEASURES_PER_HOUR; minuteDecade++)
		{
			if (g_timeArray[hour][minuteDecade] & CELL_TAGGED_MASK)
			{
				if ((g_timeArray[hour][minuteDecade] > g_timeArray[highestTempOfTheDayHour][highestTempOfTheDayMinuteDecade]) || (highestTempOfTheDayHour == INVALID_CELL))
				{
					highestTempOfTheDayHour = hour;
					highestTempOfTheDayMinuteDecade = minuteDecade;
				}
				
				if ((g_timeArray[hour][minuteDecade] < g_timeArray[lowestTempOfTheDayHour][lowestTempOfTheDayMinuteDecade]) || (lowestTempOfTheDayHour == INVALID_CELL))
				{
					lowestTempOfTheDayHour = hour;
					lowestTempOfTheDayMinuteDecade = minuteDecade;
				}
			}
		}
	}
	
	buf_cls();
	buf_locate(0,0);
	
	if (highestTempOfTheDayHour != INVALID_CELL)
	{
		if ((g_timeArray[highestTempOfTheDayHour][highestTempOfTheDayMinuteDecade] & HALF_MASK) != 0)
		{
			half = '5';
		}
		
		sprintf(slotString,"Max %02i:%02i %02i.%c%cC", highestTempOfTheDayHour, highestTempOfTheDayMinuteDecade * 10, (g_timeArray[highestTempOfTheDayHour][highestTempOfTheDayMinuteDecade] >> 4), half, CELCIUS_SIGN);
	}
	else
	{
		sprintf(slotString,"Max      NO DATA");
	}
	
	buf_str(slotString);
	buf_locate(1,0);
	
	if (lowestTempOfTheDayHour != INVALID_CELL)
	{
		if ((g_timeArray[lowestTempOfTheDayHour][lowestTempOfTheDayMinuteDecade] & HALF_MASK) != 0)
		{
			half = '5';
		}
		
		sprintf(slotString,"Min %02i:%02i %02i.%c%cC", lowestTempOfTheDayHour, lowestTempOfTheDayMinuteDecade * 10, (g_timeArray[lowestTempOfTheDayHour][lowestTempOfTheDayMinuteDecade] >> 4), half, CELCIUS_SIGN);
	}
	else
	{
		sprintf(slotString,"Min      NO DATA");
	}
	
	buf_str(slotString);
}

//******************** WARSTWA 2 ********************************
void SpecificTimeWindow_Event()
{
	char slotString[17];
	int16_t temperature = g_timeArray[g_specificHour][g_specificMinute / 10];
	char half = '0';
	active_buf = g_specificTime_layer.buf;
	
	buf_cls();
	buf_locate(0,0);
	sprintf(slotString,"Temp       Hour");
	buf_str(slotString);
	buf_locate(1,0);
	
	if (temperature & ~CELL_TAGGED_MASK)
	{
		if ((temperature & HALF_MASK) != 0)
		{
			half = '5';
		}
		
		if (temperature >= 0)
		{
			sprintf(slotString,"%02i.%c%cC     %02i:%02i",(temperature >> 4), half, CELCIUS_SIGN,  g_specificHour, g_specificMinute);
		}
		else
		{
			sprintf(slotString,"%02i.%c%cC   %02i:%02i",(temperature >> 4), half, CELCIUS_SIGN,  g_specificHour, g_specificMinute);
		}
	}
	else
	{
		sprintf(slotString,"NO DATA @  %02i:%02i",g_specificHour, g_specificMinute);
	}
	
	buf_str(slotString);
}


