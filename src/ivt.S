; Defines the interrupt vector table for the project

.section .ivt
    jmp main    ; RESET: jumps to main
    reti        ; INT0
    reti        ; INT1
    reti        ; PCINT0
    reti        ; PCINT1
    reti        ; PCINT2
    reti        ; WDT
    reti        ; TIMER2 COMPA
    reti        ; TIMER2 COMPB
    reti        ; TIMER2 OVF
    reti        ; TIMER1 CAPT
    reti        ; TIMER1 COMPA
    reti        ; TIMER1 COMPB
    reti        ; TIMER1 OVF
    reti        ; TIMER0 COMPA
    reti        ; TIMER0 COMPB
    reti        ; TIMER0 OVF
    reti        ; SPI, STC
    reti        ; USART, RX
    reti        ; USART, UDRE
    reti        ; USART, TX
    reti        ; ADC
    reti        ; EE READY
    reti        ; ANALOG COMP
    reti        ; TWI
    reti        ; SPM READY