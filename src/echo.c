#include "echo.h"
#include "usart.h"

int echo(int argc, char *args[])
{
    for (int i = 0; i < argc; i++)
    {
        usart_transmit_flash_string("-> ");
        usart_transmit_string(args[i]);
        usart_transmit_flash_string("\r\n");
    }
    return 0;
}
