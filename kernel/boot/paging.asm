bits 32

section .text

global setup_page_tables
setup_page_tables:
    mov eax, pdp
    or eax, 0b11           ; Present + Writable.
    mov [pml4], eax

    mov eax, pd
    or eax, 0b11           ; Present + Writable.
    mov [pdp], eax

    mov ecx, 0

    .loop:
        mov eax, 0x200000  ; 2MiB
        mul ecx
        or eax, 0b10000011 ; Present + Writable + Huge Page.
        mov [pd + ecx * 8], eax
        inc ecx,
        cmp ecx, 512
        jne .loop

    ret

global enable_paging
enable_paging:
    ; Enable PAE.
    mov eax, cr4
    or eax, 1 << 5      ; CR4.PAE = 1
    mov cr4, eax

    ; Set LME.
    mov ecx, 0xC0000080 ; EFER MSR
    rdmsr
    or eax, 1 << 8      ; EFER.LME = 1
    wrmsr

    mov eax, pml4
    mov cr3, eax

    ; Enable paging.
    mov eax, cr0
    or eax, 1 << 31     ; CR0.PG = 1
    mov cr0, eax

    ret

section .bss
align 4096

pml4:
    resb 4096 ; 4KiB
pdp:
    resb 4096 ; 4KiB
pd:
    resb 4096 ; 4KiB
