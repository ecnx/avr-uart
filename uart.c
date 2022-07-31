/* ------------------------------------------------------------------
 * UART Library for AVR Devices
 * ------------------------------------------------------------------ */

#include "uart.h"

/**
 * UART Interface baudrate calculation
 */
#define BAUD_PRESCALE (((F_CPU / (UART_CONFIG_BAUDRATE * 16UL))) - 1)

/**
 * Initialize UART Interface
 */
static void uart_init ( void )
{
    /* Set the baudrate */
    UBRRL = BAUD_PRESCALE;
    UBRRH = BAUD_PRESCALE >> 8;
    /* Enable the interface */
    UCSRB = _BV ( TXEN ) | _BV ( RXEN );
    /* Use 8N1 with two stop bits */
    UCSRC = _BV ( URSEL ) | _BV ( USBS ) | _BV ( UCSZ0 ) | _BV ( UCSZ1 );
}

/**
 * Initialize UART Interface with RXD pullup
 */
void uart_init_with_rxd_pullup ( void )
{
    /* Set RXD as input */
    UART_CONFIG_DDR &= ~_BV ( UART_CONFIG_RXD );
    /* Enable RXD pullup */
    UART_CONFIG_PORT |= _BV ( UART_CONFIG_RXD );
    /* Default UART init */
    uart_init (  );
}

/**
 * Initialize UART Interface without RXD pullup
 */
void uart_init_no_rxd_pullup ( void )
{
    /* Set RXD as input */
    UART_CONFIG_DDR &= ~_BV ( UART_CONFIG_RXD );
    /* Disable RXD pullup */
    UART_CONFIG_PORT &= ~_BV ( UART_CONFIG_RXD );
    /* Default UART init */
    uart_init (  );
}

/**
 * Uninitialize UART Interface
 */
void uart_uninit ( void )
{
    /* Disable the interface */
    UCSRB = 0;
}

/**
 * Send data byte via UART Interface
 */
void uart_tx_byte ( uint8_t byte )
{
    /* Wait until not busy */
    while ( !( UCSRA & _BV ( UDRE ) ) );
    /* Send input byte */
    UDR = byte;
    /* Wait until not busy */
    while ( !( UCSRA & _BV ( UDRE ) ) );
}

/**
* Send data bytes via UART Interface
 */
void uart_tx_data ( const uint8_t * data, size_t len )
{
    const uint8_t *end;

    for ( end = data + len; data != end; data++ )
    {
        uart_tx_byte ( *data );
    }
}

/**
 * Check for UART Interface data available
 */
int8_t uart_data_available ( void )
{
    return UCSRA & _BV ( RXC );
}

/**
 * Receive data byte via UART Interface
 */
uint8_t uart_rx_byte ( void )
{
    /* Await operation completed */
    while ( !uart_data_available (  ) );
    /* Return received byte */
    return UDR;
}

/**
 * Receive data bytes via UART Interface
 */
void uart_rx_data ( uint8_t * data, size_t len )
{
    const uint8_t *end;

    for ( end = data + len; data != end; data++ )
    {
        *data = uart_rx_byte (  );
    }
}
