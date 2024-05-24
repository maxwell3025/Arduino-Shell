#include <avr/io.h>
#include "scheduler.h"
#include "usart.h"

enum ProgramState
{
    RUNNING,
    PENDING,
};

struct Program
{
    unsigned int sp;
};

#define num_programs (*((unsigned int *)RAMSTART))
#define current_program (*((unsigned int *)RAMSTART + 0x04))

void init()
{
    // num_programs = 1;
}

void context_switch()
{
    usart_transmit_flash_string("Context Switch\r\n");
}