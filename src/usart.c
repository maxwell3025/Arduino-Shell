#include <avr/io.h>
#include <avr/pgmspace.h>
#include "usart.h"

#define BAUD 9600
#define UBRR (F_CPU / 16 / BAUD - 1)

void usart_init()
{
    UBRR0H = (unsigned char)(UBRR >> 8);
    UBRR0L = (unsigned char)(UBRR);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void usart_transmit(unsigned char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
}

unsigned char usart_receive()
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}

void usart_transmit_flash_string(char *str)
{
    unsigned char c;
    while (c = pgm_read_byte(str++))
    {
        usart_transmit(c);
    }
}

void usart_transmit_string(char *str)
{
    while (*str)
    {
        usart_transmit(*str);
        str++;
    }
}

char _convert_hex(char x)
{
    char v = x & 0xf;
    if (v < 10)
    {
        return '0' + v;
    }
    else if (v < 16)
    {
        return 'A' - 10 + v;
    }
    else
    {
        return 'X';
    }
}

void usart_transmit_hex_number(unsigned int x)
{
    usart_transmit('0');
    usart_transmit('x');
    usart_transmit(_convert_hex(x >> 12));
    usart_transmit(_convert_hex(x >> 8));
    usart_transmit(_convert_hex(x >> 4));
    usart_transmit(_convert_hex(x >> 0));
}
