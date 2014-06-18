/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the VirtualSerial demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "VirtualSerial.h"
#include "ds18b20.h"
#include "hardware.h"
#include "i2c_twi.h"
#include "data_collect.h"
#include "lcd44780.h"
#include "buf_lcd.h"
#include "warstwy.h"

#include <string.h>

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber   = 0,
				.DataINEndpoint           =
					{
						.Address          = CDC_TX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.DataOUTEndpoint =
					{
						.Address          = CDC_RX_EPADDR,
						.Size             = CDC_TXRX_EPSIZE,
						.Banks            = 1,
					},
				.NotificationEndpoint =
					{
						.Address          = CDC_NOTIFICATION_EPADDR,
						.Size             = CDC_NOTIFICATION_EPSIZE,
						.Banks            = 1,
					},
			},
	};

/** Standard file stream for the CDC interface when set up, so that the virtual CDC COM port can be
 *  used like any regular character stream in the C APIs
 */
static FILE USBSerialStream;

uint8_t g_rxBuffer[MAX_BUFFER_SIZE];
uint8_t g_txBuffer[MAX_BUFFER_SIZE];
uint8_t g_nrOfBytes2Receive = DEFAULT_NR_OF_BYTES; // default value
uint8_t	g_packetStatus = PACKET_UNINITIALISED;
uint8_t *g_ds18b20RomValuePointer; // yep uint8_t not uint64_t, thats on purpose

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	uint8_t uartReceivedByte = 0;
	uint8_t currentByteNr = 0;
	uint8_t calculatedCrc = 0;
	g_ds18b20RomValuePointer = &g_ds18b20RomValue;
	uint8_t prevSecRead = 0xFF;
	SetTimeMeasure_Flag();
	
	SetupHardware();
	i2cSetBitrate(100);
	
	memset(&g_timeArray, 0, sizeof(g_timeArray));
	
	// utworzenie kilku obiektów/warstw na potrzeby zdarzenia BUF_LCD_EVENT()
	create_obj(&g_dateAndTime_layer,			0,	0,	COLS,	ROWS,	0,	DateDisplayWindow_Event);
	create_obj(&g_lowestAndHighestTemp_layer,	0,	0,	COLS,	ROWS,	0,	LowestHighestTempWindow_Event);
	create_obj(&g_specificTime_layer,			0,	0,	COLS,	ROWS,	0,	SpecificTimeWindow_Event);
	g_activeLayer = DATE_AND_TIME_MASK;

	/* Create a regular character stream for the interface so that it can be used with the stdio.h functions */
	CDC_Device_CreateStream(&VirtualSerial_CDC_Interface, &USBSerialStream);
	
	// Read sensors ID, set scratchpad and read temp
	if	(
		(ds18b20_ReadROM(OWI_PIN_1, &g_ds18b20RomValue)) ||
		(ds18b20_WriteScratchpad(OWI_PIN_1, DS18B20_MAX_ALARM_TEMP, DS18B20_MIN_ALARM_TEMP, DS18B20_MIN_RESOLUTION)) ||
		(ds18b20_ReadTemp(OWI_PIN_1, g_ds18b20TempValue))
		)
	{
		LLedOn(); // couldnt read hardware
	}

	// debug
	g_time = ds1307_GetCurrentTime();
	g_date = ds1307_GetCurrentDate();
	
	GlobalInterruptEnable();

	while(1)
	{
		CheckCurrentVisibleLayer();
		
		if (CDC_Device_BytesReceived(&VirtualSerial_CDC_Interface))
		{
			uartReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
			g_rxBuffer[currentByteNr] = uartReceivedByte;
			
			if (currentByteNr > MAX_BUFFER_SIZE)
			{
				currentByteNr = 0;
				g_packetStatus = PACKET_UNINITIALISED;
			}
			
			if (!currentByteNr && (SYNC_BYTE == uartReceivedByte))
			{
				currentByteNr = 0;
				g_packetStatus = PACKET_SYNCED;
			}
			else if ((1 == currentByteNr) && (PACKET_SYNCED == g_packetStatus))
			{
				switch(uartReceivedByte)
				{
					case CMD_SET_TIME:
					{
						g_nrOfBytes2Receive = 4; // total nr of frames -2
						break;
					}
					
					case CMD_SET_DATE:
					{
						g_nrOfBytes2Receive = 5;
						break;
					}
					
					case CMD_GET_HOUR_TEMP:
					{
						g_nrOfBytes2Receive = 3;
						break;
					}
					
					case CMD_GET_TIME:
					case CMD_GET_DATE:
					case CMD_GET_CURR_TEMP:
					case CMD_GET_DS18B20_HID:
					{
						g_nrOfBytes2Receive = 1;
						break;
					}
					
					default:
					{
						// unknown frame
						g_nrOfBytes2Receive = DEFAULT_NR_OF_BYTES;
						currentByteNr = 0;
						g_packetStatus = PACKET_UNINITIALISED;
						break;
					}
				}
			}
			else if ((currentByteNr >= (g_nrOfBytes2Receive + 1)) && (PACKET_SYNCED == g_packetStatus))
			{
				calculatedCrc = GetCrc(g_rxBuffer, currentByteNr);
				
				if (calculatedCrc == g_rxBuffer[currentByteNr])
				{
					g_packetStatus = PACKET_CRC_OK;
				}
				else //  crc error
				{
					currentByteNr = 0;
					g_packetStatus = PACKET_UNINITIALISED;
					g_nrOfBytes2Receive = DEFAULT_NR_OF_BYTES;
				}
			}
			
			if (PACKET_SYNCED == g_packetStatus)
			{
				currentByteNr++;
			}
			
			//////////////////////////////////////////////////////////////////////////
			
			if (PACKET_CRC_OK == g_packetStatus)
			{
				volatile uint8_t i = 0;
				
				currentByteNr = 0;
				g_packetStatus = PACKET_UNINITIALISED;
				
				switch (g_rxBuffer[1])
				{
					case CMD_SET_TIME:
					{
						g_time.second = g_rxBuffer[2];
						g_time.minute = g_rxBuffer[3];
						g_time.hour = g_rxBuffer[4];
						ds1307_SetCurrentTime(&g_time);
						
						SendAnsferAfterSetCommand(g_rxBuffer[1]);
						break;
					}
					
					case CMD_GET_TIME:
					{
						g_time = ds1307_GetCurrentTime();
						
						g_txBuffer[i++] = SYNC_BYTE; // sync byte
						g_txBuffer[i++] = g_rxBuffer[1]; // command
						g_txBuffer[i++] = g_time.second;
						g_txBuffer[i++] = g_time.minute;
						g_txBuffer[i++] = g_time.hour;
						g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
						i++;
						CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
						break;
					}
					
					case CMD_SET_DATE:
					{
						g_date.day = g_rxBuffer[2];
						g_date.date = g_rxBuffer[3];
						g_date.month = g_rxBuffer[4];
						g_date.year = g_rxBuffer[5];
						ds1307_SetCurrentDate(&g_date);
						
						SendAnsferAfterSetCommand(g_rxBuffer[1]);
						break;
					}
					
					case CMD_GET_DATE:
					{
						g_date = ds1307_GetCurrentDate();
						
						g_txBuffer[i++] = SYNC_BYTE; // sync byte
						g_txBuffer[i++] = g_rxBuffer[1]; // command
						g_txBuffer[i++] = g_date.day;
						g_txBuffer[i++] = g_date.date;
						g_txBuffer[i++] = g_date.month;
						g_txBuffer[i++] = g_date.year;
						g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
						i++;
						CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
						break;
					}
					
					case CMD_GET_CURR_TEMP:
					{
						ds18b20_ReadTemp(OWI_PIN_1, g_ds18b20TempValue);
						
						g_txBuffer[i++] = SYNC_BYTE; // sync byte
						g_txBuffer[i++] = g_rxBuffer[1]; // command
						g_txBuffer[i++] = g_ds18b20TempValue[0] |= CELL_TAGGED_MASK; // valid temp just for current read
						g_txBuffer[i++] = g_ds18b20TempValue[1];
						g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
						i++;
						CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
						break;
					}
					
					case CMD_GET_HOUR_TEMP:
					{
						g_txBuffer[i++] = SYNC_BYTE; // sync byte
						g_txBuffer[i++] = g_rxBuffer[1]; // command
						g_txBuffer[i++] = (uint8_t)g_timeArray[g_rxBuffer[3]][g_rxBuffer[2] / 10];
						g_txBuffer[i++] = (uint8_t)(g_timeArray[g_rxBuffer[3]][g_rxBuffer[2] / 10] >> 8);
						g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
						i++;
						CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
						break;
					}
					
					case CMD_GET_DS18B20_HID:
					{
						g_txBuffer[i++] = SYNC_BYTE; // sync byte
						g_txBuffer[i++] = g_rxBuffer[1]; // command
						
						for (; i < 10; i++)
						{
							g_txBuffer[i] = *(g_ds18b20RomValuePointer + i -2);
						}
						
						g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
						i++;
						CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
						break;
					}
					
					default:
					{
						// add handler
						break;
					}
				}
			}
		}

		if(!GetTimeMeasure_Flag())
		{
			g_time = ds1307_GetCurrentTime();
			g_date = ds1307_GetCurrentDate();
			RxLedToggle();
			SetTimeMeasure_Flag();
		}
		
		if (g_time.second != prevSecRead)
		{
			ds18b20_ReadTemp(OWI_PIN_1, g_ds18b20TempValue);
			prevSecRead = g_time.second;
		}
		
		if (!((g_time.minute % DATA_STORE_INTERVAL_MIN) | (g_time.second % DATA_STORE_INTERVAL_MIN)))
		{
			if (!(g_timeArray[g_time.hour][g_time.minute / 10] & CELL_TAGGED_MASK))
			{
				g_timeArray[g_time.hour][g_time.minute / 10] = g_ds18b20TempValue[0] | (g_ds18b20TempValue[1] << 8);
				g_timeArray[g_time.hour][g_time.minute / 10] |= CELL_TAGGED_MASK;
				NOP();
			}
		}
		
		ButtonsTimeChange();
		
		BARREL_EVENT(1);	// zdarzenie obs³ugi warstw LCD i procesów

		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		USB_USBTask();
	} // end while
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
#if (ARCH == ARCH_AVR8)
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);
#elif (ARCH == ARCH_XMEGA)
	/* Start the PLL to multiply the 2MHz RC oscillator to 32MHz and switch the CPU core to run from it */
	XMEGACLK_StartPLL(CLOCK_SRC_INT_RC2MHZ, 2000000, F_CPU);
	XMEGACLK_SetCPUClockSource(CLOCK_SRC_PLL);

	/* Start the 32MHz internal RC oscillator and start the DFLL to increase it to 48MHz using the USB SOF as a reference */
	XMEGACLK_StartInternalOscillator(CLOCK_SRC_INT_RC32MHZ);
	XMEGACLK_StartDFLL(CLOCK_SRC_INT_RC32MHZ, DFLL_REF_INT_USBSOF, F_USB);

	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
#endif

	/* Hardware Initialization */
	USB_Init();
	Led_Init();
	Buttons_Init();
	TimeCheckTimer0_Init();
	TimerPushTimeout1_Init();
	TimerDebounce3_Init();
	buf_lcd_init();
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void)
{
	
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void)
{
	
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void)
{
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
}

/** Calculates the crc of frame set as buffer parameter */
uint8_t GetCrc(uint8_t *buffer, uint8_t bytes)
{
	volatile uint16_t i;
	volatile uint8_t temp = 0;
	
	for(i = 0; i < bytes ;i++)
	{
		temp += *buffer++;
	}
	temp =~ temp;
	
	return temp;
}

void SendAnsferAfterSetCommand(uint8_t command)
{
	uint8_t i = 0;
	
	g_txBuffer[i++] = SYNC_BYTE; // sync byte
	g_txBuffer[i++] = command; // command
	g_txBuffer[i] = GetCrc(g_txBuffer, i); // calculate crc
	i++;
	CDC_Device_SendData(&VirtualSerial_CDC_Interface, g_txBuffer, i); // send the ansfer back
}

void ButtonsTimeChange()
{
	static uint32_t counter = 0;
	
	if ((bit_is_clear(BTN3_PIN, BTN3_P)) && g_startFastTimeSwap)
	{
		counter++;
		
		if (counter >= MAX_BTN_COUNTER_VAL)
		{
			IncrementTimeCell();
			counter = 0;
		}
	}
	else if ((bit_is_clear(BTN1_PIN, BTN1_P)) && g_startFastTimeSwap)
	{
		counter++;
		
		if (counter >= MAX_BTN_COUNTER_VAL)
		{
			DecrementTimeCell();
			counter = 0;
		}
	}
	else
	{
		counter = 0;
		g_startFastTimeSwap = false;
	}
}
