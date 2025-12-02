bits 64

section .text

global long_mode_start
long_mode_start:
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    extern kernel_main
    call kernel_main

    ; Clear interrupts and hang later if kernel_main fails.
    cli

    .hang:
        hlt
        jmp .hang
