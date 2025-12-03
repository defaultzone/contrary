bits 32

MBMAGIC_EAX_ON_LOAD   equ 0x36D76289
CPUID_EXTENSIONS      equ 0x80000000
CPUID_EXT_FEATURES    equ 0x80000001
CPUID_EDX_EXT_FEAT_LM equ 1 << 29

section .text

; Perform general hardware and environment
; checks (Multiboot2, CPUID, Long Mode).
;
; Jumps to throw_error if any check fails.
global do_general_tests
do_general_tests:
    call test_multiboot
    call test_cpuid
    call test_long_mode
    ret

; Check if we have been loaded by a multiboot2 loader.
;
; Jumps to throw_error if we encounter an issue.
test_multiboot:
    cmp eax, MBMAGIC_EAX_ON_LOAD
    jne .fail
    ret

    .fail:
        mov eax, ERR_NO_MULTIBOOT
        jmp throw_error

; Check if CPUID is supported.
;
; Prior to using the CPUID instruction, we should also make sure the
; processor supports it by testing the 'ID' bit (0x200000) in eflags.
; This bit is modifiable only when the CPUID instruction is supported.
; For systems that don't support CPUID, changing the 'ID' bit will have
; no effect. Based on the http://wiki.osdev.org/CPUID implementation.
;
; Jumps to throw_error if we encounter an issue.
test_cpuid:
    pushfd
    pop eax
    mov ebx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ebx
    popfd
    xor eax, ebx
    jz .fail
    ret

    .fail:
        mov eax, ERR_NO_CPUID
        jmp throw_error

; Check if the CPU supports long mode.
; Based on the https://wiki.osdev.org/Setting_Up_Long_Mode implementation.
;
; Jumps to throw_error if we encounter an issue.
test_long_mode:
    mov eax, CPUID_EXTENSIONS
    cpuid
    cmp eax, CPUID_EXT_FEATURES
    jb .fail

    mov eax, CPUID_EXT_FEATURES
    cpuid
    test edx, CPUID_EDX_EXT_FEAT_LM
    jz .fail
    ret

    .fail:
        mov eax, ERR_NO_LONG_MODE
        jmp throw_error

; Print error message to the VGA buffer and halt after it.
;
; Arguments:
;   EAX - Error string source.
throw_error:
    mov esi, eax     ; Error string source.
    mov edi, 0xB8000 ; VGA buffer.
    mov ah, 0x4F     ; VGA color (red on black).

    .loop:
        lodsb        ; Next byte from string (ESI -> AL).
        or al, al    ; Check null terminator.
        jz .end

        mov [edi], ax
        add edi, 2

        jmp .loop
    .end:

    hlt

section .rodata

ERR_NO_MULTIBOOT db "ERR: MULTIBOOT NOT SUPPORTED", 0x0
ERR_NO_CPUID     db "ERR: CPUID NOT PRESENT", 0x0
ERR_NO_LONG_MODE db "ERR: LONG MODE NOT SUPPORTED", 0x0
