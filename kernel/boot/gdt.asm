bits 64

section .rodata
align 16

gdt:
    ; Null descriptor.
    dq 0x0000000000000000

    .seg_kernel_code:
        dw 0xFFFF     ; Limit low.
        dw 0x0        ; Base low.
        db 0x0        ; Base mid.
        db 0b10011010 ; Flags: 4KB granularity, 64-bit segment, limit high.
        db 0b10101111 ; Flags [4 bits] (4KB, _, long-mode, _) << 4 | limit high.
        db 0x0        ; Base high.
gdt_end:

global gdt_ptr
gdt_ptr:
    dw gdt_end - gdt - 1 ; Limit.
    dd gdt               ; Address.

global SEG_KERNEL_CODE
SEG_KERNEL_CODE equ gdt.seg_kernel_code - gdt
