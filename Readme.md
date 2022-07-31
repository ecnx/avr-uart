# avr-i2c
UART Library for AVR Atmega328p

Example:
```
uint8_t data[4];
uart_init_with_rxd_pullup();
uart_tx_byte('b');
uart_rx_data(data, sizeof(data));
if (uart_data_available()) {
    uart_tx_byte('x');
}
uart_uninit();
```
