#include <avr/io.h>
#ifndef __ASSEMBLER__
#define num_programs (*((unsigned int *)(unsigned char *)(RAMSTART)))
#define current_program_index (*((unsigned int *)(unsigned char *)(RAMSTART + 0x04)))
#define current_program (*((struct Program *)(unsigned char *)(RAMSTART + 0x08)))
#define current_program_register(r) (*((unsigned char *)(unsigned char *)(RAMSTART + 0x08 + r)))
#else
#define num_programs (RAMSTART)
#define current_program_index (RAMSTART + 0x04)
#define current_program (RAMSTART + 0x08)
#define current_program_register(r) (RAMSTART + 0x08 + r)
#define current_program_sp_l (RAMSTART + 0x28)
#define current_program_sp_h (RAMSTART + 0x29)
#endif