bits 64

%macro define_isr 1
    global isr%+%1
    isr%+%1:
        %ifndef has_error_code
            push 0
        %endif

        push %1
        push rax
        push rbx
        push rcx
        push rdx
        push rbp
        push rsi
        push rdi
        
        cld

        extern exception_handler
        call exception_handler

        pop rdi
        pop rsi
        pop rbp
        pop rdx
        pop rcx
        pop rbx
        pop rax
        add esp, 8 
        iretq
%endmacro

%assign i 0
%rep 32
    %if i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 17 || i == 21 || i == 29 || i == 30
        %define has_error_code
    %endif

    define_isr i

    %undef has_error_code
    %assign i i+1
%endrep
