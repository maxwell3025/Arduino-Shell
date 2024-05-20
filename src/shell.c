#include "usart.h"
#include "util.h"

int main()
{
    usart_init();
    char command_buffer[128];
    unsigned int command_length;
    while (1)
    {
        unsigned char c = usart_receive();
        switch (c)
        {
        case '\r':
            // TODO execute command
            usart_transmit_flash_string("\r\n$ ");
            break;

        case '\b':
        case 0x7F:
            usart_transmit_flash_string("\b \b");
            command_buffer[--command_length] = '\0';
            break;

        default:
            if (is_printing(c))
            {
                usart_transmit(c);
            }
            else
            {
                usart_transmit_hex_number(c);
            }
            command_buffer[command_length++] = c;
            break;
        }
    }
}
