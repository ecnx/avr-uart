/* ------------------------------------------------------------------
 * UART Library for AVR Devices
 * ------------------------------------------------------------------ */

#ifndef UART_LIBRARY_H
#define UART_LIBRARY_H

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Config Example for Atmega328p
 * #define UART_CONFIG_BAUDRATE 9600
 * #define UART_CONFIG_DDR DDRD
 * #define UART_CONFIG_PORT PORTD
 * #define UART_CONFIG_TXD PD1
 * #define UART_CONFIG_RXD PD0
 */

#include "uart-config.h"

/**
 * Initialize UART Interface with RXD pullup
 */
extern void uart_init_with_rxd_pullup ( void );

/**
 * Initialize UART Interface without RXD pullup
 */
extern void uart_init_no_rxd_pullup ( void );

/**
 * Uninitialize UART Interface
 */
extern void uart_uninit ( void );

/**
 * Send data byte via UART Interface
 */
extern void uart_tx_byte ( uint8_t byte );

/**
* Send data bytes via UART Interface
 */
extern void uart_tx_data ( const uint8_t * data, size_t len );

/**
 * Receive data byte via UART Interface
 */
extern uint8_t uart_rx_byte ( void );

/**
 * Check for UART Interface data available
 */
extern int8_t uart_data_available ( void );

/**
 * Receive data bytes via UART Interface
 */
extern void uart_rx_data ( uint8_t * data, size_t len );

#endif
