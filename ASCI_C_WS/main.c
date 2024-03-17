/*
 * main.c
 *
 *  Created on: Dec 15, 2023
 *      Attendance System
 *      Computer Interface - ASCI Project
 *      Author : Muhammad Salah
 */

#include <avr/io.h>
#include <avr/delay.h>
#include <stddef.h>  // For NULL definition
#include "uart.h"
#include "gpio.h"
#include <string.h>


/* Global Variables */

uint8 BUFFER_SIZE = 15;
uint8 buffer[15]={0};
uint8 temp[15]={0};
int buffer_index = 0;


int main()
{
	/* Leds Initialization */
	GPIO_setupPinDirection(PORTA_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN6_ID,PIN_OUTPUT);

	/* System Initialization Red Led Indicatior Time */
	GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_HIGH);
	_delay_ms(1000);
	/* UART Initialization with baud rate = 9600bps */
	UART_init(9600);
	/* Turning Red led off */
	GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_LOW);
	/* Local Variables Initialization */
	uint8 tag_byte=0;
	uint8 sendFlag=0;
	uint16 response=0;
	//memset(buffer,0,15); memset could be used to initializae the buffer

	while (1)
	{
		/* Turn ON green led as indicator to insert the tag */
		GPIO_writePin(PORTA_ID,PIN4_ID,LOGIC_HIGH);
		/* Read the 14 number of Tag */
		for (int i=0;i<14;i++)
		{
			tag_byte = UART_recieveByte();
			buffer[i] = tag_byte;
		}
		_delay_us(15);
		/* Checking if the inserted tag not repeated */
		for (int i=0;i<5;i++)
		{
			if (buffer[i]!=temp[i])
			{
				sendFlag=1;
				break;
			}
		}

		/* If a new tag -not repeated- , send its value to the GUI through UART */
		if (sendFlag)
		{
			/* Each tag should be sent between a start byte and end byte
			 * Start Byte : '!'
			 * End Byte : '$'
			 */
			UART_sendByte('!');

			/* Tag Bytes */
			for (int i=0;i<5;i++)
			{
				temp[i]=buffer[i];
				if (buffer[i]>'9'||buffer[i]<'0')
				{
					buffer[i]='1'; // To send only numbers to be reigsterd in DB
				}
				UART_sendByte(buffer[i]);
			}
			/* End Byte */
			UART_sendByte('$');

			/* Reinitialize The flag */
			sendFlag=0;

			/* For Each Tag , The embedded system should receive
			 * a response , from GUI and its DB
			 * if tag is already registered the Led indicator should turn on
			 * to allow user to enter
			 * if tag isn't matched , a buzzer would turn on!
			 */

			do {
				response =UART_recieveByte();

				/* A positive response is equal to @ , Tag is matched */
				if (response=='@')
				{
					GPIO_writePin(PORTA_ID,PIN4_ID,LOGIC_LOW);
					GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_HIGH);
					_delay_ms(2000);
					GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_LOW);
					break;
				}
				/* Negative response is equal to # , Tag isn't matched */
				else if (response=='#')
				{
					GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_HIGH);
					_delay_ms(500);
					GPIO_writePin(PORTC_ID,PIN6_ID,LOGIC_LOW);
					break;
				}
			}
			while (response!='@'||response!='#');

		}
		response='-1'; // Reinitialize the response value
	}

}


