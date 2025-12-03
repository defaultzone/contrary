bits 32

section .text

global start
start:
    cli

    mov ebp, stack_top
    mov esp, ebp

    extern do_general_tests
    call do_general_tests

    extern setup_page_tables
    call setup_page_tables

    extern enable_paging
    call enable_paging

    extern gdt_ptr
    lgdt [gdt_ptr]

    extern SEG_KERNEL_CODE, long_mode_start
    call SEG_KERNEL_CODE:long_mode_start

section .bss

align 4096

stack_bottom:
    resb 4096 * 4 ; 16KB
stack_top:
