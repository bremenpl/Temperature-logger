#ifndef I2C_TWI_H_
#define I2C_TWI_H_

#include <stdint.h>

#define ACK 1
#define NACK 0

#define DS1307_ADDR			0xD0

#define TIME_ADDR_START		0
#define TIME_SIZE			3

#define DATE_ADDR_START		3
#define DATE_SIZE			4

typedef struct  
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
} TIME_t;

extern TIME_t g_time;

typedef struct  
{
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} DATE_t;

extern DATE_t g_date;

// funkcje

void i2cSetBitrate(uint16_t bitrateKHz);

void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8_t bajt);
uint8_t TWI_read(uint8_t ack);

void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf );
void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);

TIME_t ds1307_GetCurrentTime();
DATE_t ds1307_GetCurrentDate();

void ds1307_SetCurrentTime(TIME_t *time);
void ds1307_SetCurrentDate(DATE_t *date);

uint8_t dec2bcd(uint8_t dec);
uint8_t bcd2dec(uint8_t bcd);

#endif /* I2C_TWI_H_ */
