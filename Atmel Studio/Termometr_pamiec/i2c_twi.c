#include <avr/io.h>

#include "i2c_twi.h"

TIME_t g_time;
DATE_t g_date;

void i2cSetBitrate(uint16_t bitrateKHz) {
	uint8_t bitrate_div;

	bitrate_div = ((F_CPU/1000l)/bitrateKHz);
	if(bitrate_div >= 16)
		bitrate_div = (bitrate_div-16)/2;

	TWBR = bitrate_div;
}

void TWI_start(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while (!(TWCR&(1<<TWINT)));
}

void TWI_stop(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while ( !(TWCR&(1<<TWSTO)));
}

void TWI_write(uint8_t bajt) {
	TWDR = bajt;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while ( !(TWCR&(1<<TWINT)));
}

uint8_t TWI_read(uint8_t ack) {
	TWCR = (1<<TWINT)|(ack<<TWEA)|(1<<TWEN);
	while ( !(TWCR & (1<<TWINT)));
	return TWDR;
}



void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf ) {

	TWI_start();
	TWI_write(SLA);
	TWI_write(adr);
	while (len--) TWI_write(*buf++);
	TWI_stop();
}



void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf) {

	TWI_start();
	TWI_write(SLA);
	TWI_write(adr);
	TWI_start();
	TWI_write(SLA + 1);
	while (len--) *buf++ = TWI_read( len ? ACK : NACK );
	TWI_stop();
}

TIME_t ds1307_GetCurrentTime()
{
	TIME_t time;
	uint8_t buffer[TIME_SIZE];
	
	TWI_read_buf(DS1307_ADDR, TIME_ADDR_START, TIME_SIZE, buffer);
	
	time.second = bcd2dec(buffer[0]);
	time.minute = bcd2dec(buffer[1]);
	time.hour = bcd2dec(buffer[2]);
	
	return time;
}

DATE_t ds1307_GetCurrentDate()
{
	DATE_t date;
	uint8_t buffer[DATE_SIZE];
	
	TWI_read_buf(DS1307_ADDR, DATE_ADDR_START, DATE_SIZE, buffer);
	
	date.day =	bcd2dec(buffer[0]);
	date.date = bcd2dec(buffer[1]);
	date.month = bcd2dec(buffer[2]);
	date.year = bcd2dec(buffer[3]);
	
	return date;
}

void ds1307_SetCurrentTime(TIME_t *time)
{
	uint8_t buffer[TIME_SIZE];
	
	buffer[0] = dec2bcd(time->second);
	buffer[1] = dec2bcd(time->minute);
	buffer[2] = dec2bcd(time->hour);
	
	TWI_write_buf(DS1307_ADDR, TIME_ADDR_START, TIME_SIZE, buffer);
}

void ds1307_SetCurrentDate(DATE_t *date)
{
	uint8_t buffer[DATE_SIZE];
	
	buffer[0] = dec2bcd(date->day);
	buffer[1] = dec2bcd(date->date);
	buffer[2] = dec2bcd(date->month);
	buffer[3] = dec2bcd(date->year);
	
	TWI_write_buf(DS1307_ADDR, DATE_ADDR_START, DATE_SIZE, buffer);
}

// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec)
{
	return ((dec / 10)<<4) | (dec % 10);
}

// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd)
{
	return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
}

