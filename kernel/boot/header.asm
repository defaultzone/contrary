MBMAGIC    equ 0xE85250D6                ; Magic number identifying Multiboot2 header.
MBARCH     equ 0                         ; 32-bit (protected) mode of i386.
MBLEN      equ header_start - header_end ; Length of the Multiboot2 header (including magic fields).
MBFIELDSUM equ MBMAGIC + MBARCH + MBLEN  ; Sum of the magic fields.
MBCHECKSUM equ 0x100000000 - MBFIELDSUM  ; Checksum for the Multiboot2 header.

section .multiboot

header_start:     ; Offset Type Field Name
    dd MBMAGIC    ; 0      u32  magic
    dd MBARCH     ; 4      u32  architecture
    dd MBLEN      ; 8      u32  header_length
    dd MBCHECKSUM ; 12     u32  checksum
    dw 0          ; 16-XX       tags
    dw 0
    dd 8
header_end:
