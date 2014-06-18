/*
 * hardware.h
 *
 * Created: 2014-03-19 23:37:57
 *  Author: Lukasz
 */ 


#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <avr/io.h>
#include <stdint.h>

#define RX_LED_DDR		DDRB
#define RX_LED_PORT		PORTB
#define RX_LED_P		0

#define TX_LED_DDR		DDRD
#define TX_LED_PORT		PORTD
#define TX_LED_P		5

#define L_LED_DDR		DDRC
#define L_LED_PORT		PORTC
#define L_LED_P			7

#define BTN1_DDR		DDRD
#define BTN1_PORT		PORTD
#define BTN1_PIN		PIND
#define BTN1_P			2

#define BTN2_DDR		DDRD
#define BTN2_PORT		PORTD
#define BTN2_PIN		PIND
#define BTN2_P			3

#define BTN3_DDR		DDRE
#define BTN3_PORT		PORTE
#define BTN3_PIN		PINE
#define BTN3_P			6

#define NOP()			asm("nop")

#define g_takeMeasureNow_Flag		GPIOR0
// GPIOR1 untaken
// GPIOR2 untaken
#define SOFT_TIMER0_PRESCALLER		5

static inline void Led_Init()
{
	RX_LED_DDR |= _BV(RX_LED_P);
	RX_LED_PORT |= _BV(RX_LED_P);
	
	TX_LED_DDR |= _BV(TX_LED_P);
	TX_LED_PORT |= _BV(TX_LED_P);
	
	L_LED_DDR |= _BV(L_LED_P);
	L_LED_PORT &= ~_BV(L_LED_P);
}

static inline void RxLedOn()
{
	RX_LED_PORT &= ~_BV(RX_LED_P);
}

static inline void RxLedOff()
{
	RX_LED_PORT |= _BV(RX_LED_P);
}

static inline void RxLedToggle()
{
	RX_LED_PORT ^= _BV(RX_LED_P);
}

static inline void TxLedOn()
{
	TX_LED_PORT &= ~_BV(TX_LED_P);
}

static inline void TxLedOff()
{
	TX_LED_PORT |= _BV(TX_LED_P);
}

static inline void TxLedToggle()
{
	TX_LED_PORT ^= _BV(TX_LED_P);
}

static inline void LLedOn()
{
	L_LED_PORT |= _BV(L_LED_P);
}

static inline void LLedOff()
{
	L_LED_PORT &= ~_BV(L_LED_P);
}

static inline void LLedToggle()
{
	L_LED_PORT ^= _BV(L_LED_P);
}

static inline void SetTimeMeasure_Flag()
{
	g_takeMeasureNow_Flag = SOFT_TIMER0_PRESCALLER;
}

static inline void ClrTimeMeasure_Flag()
{
	g_takeMeasureNow_Flag = 0;
}

static inline void SubstractTimeMeasure_Flag()
{
	g_takeMeasureNow_Flag--;
}

static inline uint8_t GetTimeMeasure_Flag()
{
	return g_takeMeasureNow_Flag;
}



#endif /* HARDWARE_H_ */