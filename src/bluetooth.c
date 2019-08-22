#include "bluetooth.h"
#include "messages.h"
#include "uart.h"


int bluetooth_init( void )
{
    uart_init(UART_232, 9600);
    messages_print("Bluetooth UART set to 9600\n\r");

    return 0;
}

void bluetooth_write( uint8_t data )
{
    uart_write(UART_232, data);
}

bool bluetooth_read( uint8_t* data )
{
    return uart_read(UART_232, data);
}
