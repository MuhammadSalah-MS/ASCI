/*
 * uart.h
 * Header file for UART communication module.
 *
 *  Created on: Oct 25, 2023
 *      Author: Muhammad Salah
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "common_macros.h"
#include "std_types.h"

/**
 * Initialize UART communication with specified baud rate.
 * @param baud_rate The desired baud rate for UART communication.
 */
void UART_init(uint32 baud_rate);

/**
 * Transmit a single byte over UART.
 * @param data The byte to be transmitted.
 */
void UART_sendByte(const uint8 data);

/**
 * Receive a single byte over UART.
 * @return The received byte.
 */
uint8 UART_recieveByte(void);

/**
 * Transmit a null-terminated string over UART.
 * @param str Pointer to the string to be transmitted.
 */
void UART_sendString(const uint8 * str);

/**
 * Receive a string until a '#' character is encountered over UART.
 * @param Str Pointer to the buffer where the received string will be stored.
 */
void UART_receiveString(uint8 *Str);

#endif /* UART_H_ */
