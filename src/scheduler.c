#include <avr/io.h>
#include "scheduler.h"
#include "usart.h"
#include "shell.h"

enum ProgramState
{
    RUNNING,
    PENDING,
};

struct Program
{
    unsigned char registers[32];
    unsigned int sp ;
};

void init()
{
    usart_init();
    // num_programs = 1;
}

void enter_kernel()
{
    
}

void begin_program(int (*program_main)(int argc, char *args[]), int argc, char *args[])
{
    (*program_main)(argc, args);
}

void dump_program(){
    for(int reg_number = 0; reg_number < 32; reg_number++){
        usart_transmit_flash_string("r");
        usart_transmit_hex_number(reg_number);
        usart_transmit_flash_string(":\t");
        usart_transmit_hex_number(current_program.registers[reg_number]);
        usart_transmit_flash_string("\r\n");
    }
    usart_transmit_flash_string("SP:\t");
    usart_transmit_hex_number(current_program.sp);
    usart_transmit_flash_string("\r\n");

    usart_transmit_flash_string("TOP:\t");
    usart_transmit_hex_number(RAMEND);
    usart_transmit_flash_string("\r\n");
    usart_transmit_flash_string("\r\n");
}

void context_switch()
{
    usart_transmit_flash_string("Context Switch\r\n");
    dump_program();
}