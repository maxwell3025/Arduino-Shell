#include <avr/io.h>
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
    cli
    call context_switch
    reti
