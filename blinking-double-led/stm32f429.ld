MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2048K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 192K
}

SECTIONS
{
    .text :
    {
        *(.vectors)    /* Kesme vektör tablosu (Önemli!) */
        *(.text)       /* Program kodları */
        *(.rodata)     /* Sabit veriler */
    } > FLASH

    .data :
    {
        *(.data)       /* Başlangıç değeri almış değişkenler */
    } > SRAM AT> FLASH

    .bss :
    {
        *(.bss)        /* Başlangıç değeri almamış değişkenler */
    } > SRAM
}
