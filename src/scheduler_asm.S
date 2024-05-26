#include <avr/io.h>
#include "scheduler_defs.h"
.section .text
.global init_asm
.global context_switch_asm

; NOTE: only jump to this when you are using the real stack
init_asm:
    ldi r24, 0x80
    ldi r25, 0x00
    sts OCR1AH, r24
    sts OCR1AL, r25

    ldi r25, 0x02
    sts TIMSK1, r25

    ldi r24, 0x00
    ldi r25, 0x00
    sts TCNT1H, r24
    sts TCNT1L, r25

    ldi r25, 0x05
    sts TCCR1B, r25

    call init
    jmp exit_kernel


context_switch_asm:
    ; save registers
    sts current_program_register(0), r0
    sts current_program_register(1), r1
    sts current_program_register(2), r2
    sts current_program_register(3), r3
    sts current_program_register(4), r4
    sts current_program_register(5), r5
    sts current_program_register(6), r6
    sts current_program_register(7), r7
    sts current_program_register(8), r8
    sts current_program_register(9), r9
    sts current_program_register(10), r10
    sts current_program_register(11), r11
    sts current_program_register(12), r12
    sts current_program_register(13), r13
    sts current_program_register(14), r14
    sts current_program_register(15), r15
    sts current_program_register(16), r16
    sts current_program_register(17), r17
    sts current_program_register(18), r18
    sts current_program_register(19), r19
    sts current_program_register(20), r20
    sts current_program_register(21), r21
    sts current_program_register(22), r22
    sts current_program_register(23), r23
    sts current_program_register(24), r24
    sts current_program_register(25), r25
    sts current_program_register(26), r26
    sts current_program_register(27), r27
    sts current_program_register(28), r28
    sts current_program_register(29), r29
    sts current_program_register(30), r30
    sts current_program_register(31), r31

    ; save stack pointer
    lds r24, SPH
    lds r25, SPL
    sts current_program_sp_h, r24
    sts current_program_sp_l, r25
    
    ; reset stack
    ldi r24, 0x08
    ldi r25, 0xFF
    sts SPH, r24
    sts SPL, r25
    call context_switch
; continue to routine for entering user space
exit_kernel:
    ; load stack pointer
    lds r24, current_program_sp_h
    lds r25, current_program_sp_l
    sts SPH, r24
    sts SPL, r25

    ; load registers
    lds r0, current_program_register(0) 
    lds r1, current_program_register(1) 
    lds r2, current_program_register(2) 
    lds r3, current_program_register(3) 
    lds r4, current_program_register(4) 
    lds r5, current_program_register(5) 
    lds r6, current_program_register(6) 
    lds r7, current_program_register(7) 
    lds r8, current_program_register(8) 
    lds r9, current_program_register(9) 
    lds r10, current_program_register(10)
    lds r11, current_program_register(11)
    lds r12, current_program_register(12)
    lds r13, current_program_register(13)
    lds r14, current_program_register(14)
    lds r15, current_program_register(15)
    lds r16, current_program_register(16)
    lds r17, current_program_register(17)
    lds r18, current_program_register(18)
    lds r19, current_program_register(19)
    lds r20, current_program_register(20)
    lds r21, current_program_register(21)
    lds r22, current_program_register(22)
    lds r23, current_program_register(23)
    lds r24, current_program_register(24)
    lds r25, current_program_register(25)
    lds r26, current_program_register(26)
    lds r27, current_program_register(27)
    lds r28, current_program_register(28)
    lds r29, current_program_register(29)
    lds r30, current_program_register(30)
    lds r31, current_program_register(31)
    reti
