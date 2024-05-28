#include <avr/io.h>
#include <stddef.h>
#include "scheduler.h"
#include "usart.h"
#include "../shell.h"

enum ProgramState
{
    RUNNING,
    PENDING,
};

struct Program
{
    unsigned char registers[32];
    unsigned int sp;
    unsigned int stack_base;
    unsigned int pid;
    enum ProgramState state;
};

struct Program *get_program_list(){
    return &current_program + 1;
}

void begin_program(int (*program_main)(int argc, char *args[]), int argc, char *args[])
{
    struct Program new_program;

    for(int i = 0; i < 32; i++){
        new_program.registers[i] = 0;
    }

    new_program.sp = RAMEND - 0x200;
    *((unsigned char *)new_program.sp) = (unsigned char)((unsigned int)(unsigned char *)(program_main) >> 0);
    new_program.sp--;
    *((unsigned char *)new_program.sp) = (unsigned char)((unsigned int)(unsigned char *)(program_main) >> 8);
    new_program.sp--;

    get_program_list()[num_programs++] = new_program;
}

void init()
{
    usart_init();
    // initialize first program
    num_programs = 0;
    begin_program(&main, 0, NULL);
    current_program = get_program_list()[0];
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