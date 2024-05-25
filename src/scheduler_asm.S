#include <avr/io.h>
#include "scheduler_defs.h"
.section .text
.global init_asm
.global context_switch_asm

; NOTE: only jump to this when you are using the real stack
init_asm:
    call usart_transmit

    ldi r24, 0x01
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
    sei
    ret;


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
    
    call context_switch
    reti
