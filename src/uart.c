#include "sapi.h"
#include "uart.h"

void uart_init( uartMap_t uart, uint32_t brate )
{
	//uartInit2(UART_USB, brate, 8, 0, 1);
	uartInit(uart, brate);
}

void uart_write( uartMap_t uart, uint8_t s )
{
    uartWriteByte(uart, s);
}

bool uart_read( uartMap_t uart, uint8_t* d )
{
	bool ret = false;
	if (uartRxReady(uart))
		ret = true;
	*d = uartRxRead(uart);
	return ret;
}
