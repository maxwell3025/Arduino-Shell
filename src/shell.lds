SECTIONS
{
    . = 0x0000;
    .text :
    {
        *(.ivt)
        . = 0x0036;
        *(.text*)
    }
    .data : { *(.rodata*) *(.data*) }
}