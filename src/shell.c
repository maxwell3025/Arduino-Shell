#include <avr/io.h>

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

int main()
{
    usart_init();
    while(1){
        unsigned char c = usart_receive();
        usart_transmit(c);
    }
}