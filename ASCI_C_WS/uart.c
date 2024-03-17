/*
 * uart.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Muhammad Salah
 */


#include "uart.h"
#include <avr/io.h>

void UART_init(uint32 baud_rate)
{
	uint16 ubrr_value = 0;

	UCSRA = (1<<U2X);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

void UART_sendByte(const uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
}

uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
    return UDR;
}

void UART_sendString(const uint8 * str)
{
	 uint8 i=0;
	 while (str[i]!='\0')
	 {
		UART_sendByte(str[i]);
		i++;
	 }
}
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
