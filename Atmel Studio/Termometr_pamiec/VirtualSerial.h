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
 *  Header file for VirtualSerial.c.
 */

#ifndef _VIRTUALSERIAL_H_
#define _VIRTUALSERIAL_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>
		#include <stdio.h>
		#include <stdint.h>
		#include <stdbool.h>
		#include <avr/sfr_defs.h>

		#include "Descriptors.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		#include <LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/Drivers/USB/USB.h>
		#include <LUFA/Platform/Platform.h>

	/* Macros and defines: */
		#define MAX_BUFFER_SIZE			15
		#define SYNC_BYTE				'^'
		
		#define DEFAULT_NR_OF_BYTES		2
		
		#define MAX_BTN_COUNTER_VAL		5000UL
	
		enum COMMAND_LIST
		{
			CMD_SET_TIME = 1,
			CMD_GET_TIME,
			CMD_SET_DATE,
			CMD_GET_DATE,
			CMD_GET_CURR_TEMP,
			CMD_GET_HOUR_TEMP,
			CMD_GET_MIN_TEMP,
			CMD_GET_MAX_TEMP,
			CMD_GET_DS18B20_HID,
		};
		
		enum PACKET_STATUS_LIST
		{
			PACKET_UNINITIALISED = 0,
			PACKET_SYNCED,
			PACKET_CRC_OK,
			PACKET_CRC_ERROR	
		};
		
		extern uint8_t g_rxBuffer[MAX_BUFFER_SIZE];
		extern uint8_t g_txBuffer[MAX_BUFFER_SIZE];
		extern uint8_t g_nrOfBytes2Receive;
		extern uint8_t g_packetStatus;
		
	/* Variables */
		

	/* Function Prototypes: */
		void SetupHardware(void);
		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		
		uint8_t GetCrc(unsigned char *buffer, unsigned char bytes);
		void SendAnsferAfterSetCommand(uint8_t command);
		void ButtonsTimeChange();

#endif

