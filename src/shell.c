#include <string.h>
#include "usart.h"
#include "util.h"

void interpret_command(char *command)
{
    char delim[] = {' ', '\0'};
    delim[0] = ' ';
    const char *args[10];
    unsigned int argc = 0;
    const char *tok = strtok(command, delim);
    while (tok != NULL)
    {
        args[argc++] = tok;
        tok = strtok(NULL, delim);
    }
    for (int i = 0; i < argc; i++)
    {
        usart_transmit_flash_string("\r\n-> ");
        usart_transmit_string(args[i]);
    }
}

int main()
{
    usart_init();
    usart_transmit_flash_string("$ ");
    char command_buffer[128];
    unsigned int command_length = 0;
    command_buffer[0] = '\0';
    while (1)
    {
        unsigned char c = usart_receive();
        switch (c)
        {
        case '\r':
            command_buffer[command_length] = '\0';
            interpret_command(command_buffer);
            command_length = 0;
            usart_transmit_flash_string("\r\n$ ");
            break;

        case '\b':
        case 0x7F:
            // Backspace or DEL
            if (command_length > 0)
            {
                usart_transmit_flash_string("\b \b");
                command_buffer[--command_length] = '\0';
            }
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
            command_buffer[command_length] = '\0';
            break;
        }
    }
}
