/*
 * ds18b20.h
 *
 * Created: 2014-03-19 23:23:54
 *  Author: Lukasz
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include "OWIPolled.h"
#include "OWIHighLevelFunctions.h"
#include "OWIBitFunctions.h"
#include "OWIcrc.h"
#include "data_collect.h"

#include <util/delay.h>
#include <stdint.h>

// functions return codes
#define OWI_NOERROR						0x00
#define OWI_ERROR_PRESENCE				0x01
#define OWI_ERROR_READ					0x02
#define OWI_ERROR_COPY					0x03

#define DS18B20_MIN_RESOLUTION			0x1F
#define DS18B20_MIN_ALARM_TEMP			(-5)
#define DS18B20_MAX_ALARM_TEMP			30

extern uint64_t g_ds18b20RomValue;
extern uint8_t g_ds18b20TempValue[9];

uint8_t ds18b20_ReadROM(uint8_t bus, uint64_t *value);
uint8_t ds18b20_ReadTemp(uint8_t bus, uint8_t *value);
uint8_t ds18b20_WriteScratchpad(uint8_t bus, uint8_t TH, uint8_t TL, uint8_t confReg);



#endif /* DS18B20_H_ */