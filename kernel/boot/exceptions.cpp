#include <contrary/boot/exceptions.h>

auto exception_handler(contrary::boot::exception_stack_frame frame) -> void {
    (void)frame;
    asm volatile ("cli; hlt");
}
