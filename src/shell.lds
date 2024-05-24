SECTIONS
{
    . = 0x0000;
    .text :
    {
        *(.ivt)
        *(.text*)
    }
    .data : { *(.rodata*) *(.data*) }
}
