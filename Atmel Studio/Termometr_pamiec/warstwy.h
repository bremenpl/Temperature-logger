/*
 * warstwy.h
 *
 *  Created on: 28-02-2012
 *      Author: Miros³aw Kardaœ
 */

#ifndef WARSTWY_H_
#define WARSTWY_H_


#define DATE_AND_TIME_MASK			(1 << 0);
#define LOWEST_HIGHEST_TEMP_MASK	(1 << 1);
#define SPECIFIC_TIME_MASK			(1 << 2);


extern int8_t w1y, w1x;
extern TWIN_t g_dateAndTime_layer;
extern TWIN_t g_lowestAndHighestTemp_layer;
extern TWIN_t g_specificTime_layer;

extern uint8_t g_activeLayer;

void CheckCurrentVisibleLayer();

void DateDisplayWindow_Event();
void LowestHighestTempWindow_Event();
void SpecificTimeWindow_Event();


#endif /* WARSTWY_H_ */
