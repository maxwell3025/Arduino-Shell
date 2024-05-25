; Defines the interrupt vector table for the project

.section .ivt
.vtable:
    jmp init_asm               ; RESET: jumps to main
    reti                       ; INT0
    nop
    reti                       ; INT1
    nop
    reti                       ; PCINT0
    nop
    reti                       ; PCINT1
    nop
    reti                       ; PCINT2
    nop
    reti                       ; WDT
    nop
    reti                       ; TIMER2 COMPA
    nop
    reti                       ; TIMER2 COMPB
    nop
    reti                       ; TIMER2 OVF
    nop
    reti                       ; TIMER1 CAPT
    nop
    jmp context_switch_asm     ; TIMER1 COMPA
    reti                       ; TIMER1 COMPB
    nop
    jmp context_switch_asm     ; TIMER1 OVF
    reti                       ; TIMER0 COMPA
    nop
    reti                       ; TIMER0 COMPB
    nop
    reti                       ; TIMER0 OVF
    nop
    reti                       ; SPI, STC
    nop
    reti                       ; USART, RX
    nop
    reti                       ; USART, UDRE
    nop
    reti                       ; USART, TX
    nop
    reti                       ; ADC
    nop
    reti                       ; EE READY
    nop
    reti                       ; ANALOG COMP
    nop
    reti                       ; TWI
    nop
    reti                       ; SPM READY
    nop
