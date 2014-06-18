/*
 * ds18b20.c
 *
 * Created: 2014-03-19 23:23:01
 *  Author: Lukasz
 */ 

#include "ds18b20.h"
#include <util/delay.h>

uint64_t g_ds18b20RomValue = 0;
uint8_t g_ds18b20TempValue[9];

uint8_t ds18b20_ReadROM(uint8_t bus, uint64_t *value)
{
	uint8_t buffer[8];
	
	if(!OWI_DetectPresence(bus))
	{
		return OWI_ERROR_PRESENCE;
	}
	
	OWI_ReadRom(buffer, bus);
	
	*value  = (uint64_t)buffer[0];
	*value += (uint64_t)buffer[1] << 8;
	*value += (uint64_t)buffer[2] << 16;
	*value += (uint64_t)buffer[3] << 24;
	*value += (uint64_t)buffer[4] << 32;
	*value += (uint64_t)buffer[5] << 40;
	*value += (uint64_t)buffer[6] << 48;
	*value += (uint64_t)buffer[7] << 56;
	
	OWI_DetectPresence(bus);
	return OWI_NOERROR;
}

uint8_t ds18b20_ReadTemp(uint8_t bus, uint8_t *value)
{
	unsigned char i = 0;
	
	if(!OWI_DetectPresence(bus))
	{
		return OWI_ERROR_PRESENCE;
	}
	
	OWI_SkipRom(bus);
	OWI_SendByte(0x44, bus);
	
	OWI_DetectPresence(bus);
	OWI_SkipRom(bus);
	OWI_SendByte(0xBE, bus);

	for(i = 0; i < 9; i++)
	{
		value[i] = OWI_ReceiveByte(bus);
	}
	value[0] &= ~CELL_TAGGED_MASK;
	
	OWI_DetectPresence(bus);
	return OWI_NOERROR;
}

uint8_t ds18b20_WriteScratchpad(uint8_t bus, uint8_t TH, uint8_t TL, uint8_t confReg)
{
	if(!OWI_DetectPresence(bus))
	{
		return OWI_ERROR_PRESENCE;
	}
	
	OWI_SkipRom(bus);
	OWI_SendByte(0x4E, bus);
	OWI_SendByte(TH, bus);
	OWI_SendByte(TL, bus);
	OWI_SendByte(confReg, bus);
	
	OWI_DetectPresence(bus);
	return OWI_NOERROR;
}

