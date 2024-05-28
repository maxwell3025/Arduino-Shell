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

struct Program *get_program_list()
{
    return &current_program + 1;
}

size_t find_program(unsigned int pid)
{
    size_t program_index = -1;
    struct Program *program_list = get_program_list();
    for (int i = 0; i < num_programs; i++)
    {
        if (program_list[i].pid == pid)
        {
            program_index = i;
            break;
        }
    }
    return program_index;
}

void begin_program(int (*program_main)(int argc, char *args[]), int argc, char *args[])
{
    struct Program new_program;

    for (int i = 0; i < 32; i++)
    {
        new_program.registers[i] = 0;
    }

    new_program.pid = 0;
    while (find_program(new_program.pid) != -1)
    {
        new_program.pid++;
    }

    new_program.stack_base = RAMEND - 0x200 - 0x200 * new_program.pid;
    new_program.sp = new_program.stack_base;
    *((unsigned char *)new_program.sp) = (unsigned char)((unsigned int)(unsigned char *)(program_main) >> 0);
    new_program.sp--;
    *((unsigned char *)new_program.sp) = (unsigned char)((unsigned int)(unsigned char *)(program_main) >> 8);
    new_program.sp--;

    new_program.state = RUNNING;

    get_program_list()[num_programs++] = new_program;
}

void init()
{
    usart_init();
    // initialize first program
    num_programs = 0;
    begin_program(&main, 0, NULL);
    begin_program(&main, 0, NULL);
    current_program = get_program_list()[0];
}

void dump_program()
{
    for (int reg_number = 0; reg_number < 32; reg_number++)
    {
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
    size_t program_index = find_program(current_program.pid);
    if (program_index == -1)
    {
        usart_transmit_flash_string("Current program does not exist. Stopping kernel");
        while (1)
            ;
    }
    get_program_list()[program_index] = current_program;
    usart_transmit_flash_string("Old PID: ");
    usart_transmit_hex_number(current_program.pid);
    usart_transmit_flash_string("\r\n");
    if (++program_index >= num_programs)
    {
        program_index -= num_programs;
    }
    current_program = get_program_list()[program_index];
    usart_transmit_flash_string("New PID: ");
    usart_transmit_hex_number(current_program.pid);
    usart_transmit_flash_string("\r\n");
    // dump_program();
}