#include <avr/io.h>
#ifndef __ASSEMBLER__
#define dereference(address, type) (*((type *)(unsigned char *)(address)))

#define num_programs dereference(RAMSTART, unsigned int)
#define current_program_index dereference(RAMSTART + 0x04, unsigned int)
#define current_program dereference(RAMSTART + 0x08, struct Program)
#define current_program_register(r) dereference(RAMSTART + 0x08 + r, unsigned char)
#else
#define num_programs (RAMSTART)
#define current_program_index (RAMSTART + 0x04)
#define current_program (RAMSTART + 0x08)
#define current_program_register(r) (RAMSTART + 0x08 + r)
#define current_program_sp_l (RAMSTART + 0x28)
#define current_program_sp_h (RAMSTART + 0x29)
#endif