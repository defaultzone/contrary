#ifndef CONTRARY_BOOT_EXCEPTIONS_H
#define CONTRARY_BOOT_EXCEPTIONS_H

#include <cstdint>

namespace contrary::boot {

struct __attribute__((packed)) exception_stack_frame final {
    std::uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    std::uint64_t vector_number, error_code;
    std::uint64_t rip, cs, rflags, rsp, ss;
}; // struct __attribute__((packed)) exception_stack_frame final

} // namespace contrary::boot

extern "C" {

extern "C" auto exception_handler(contrary::boot::exception_stack_frame frame) -> void;

auto isr0() -> void;
auto isr1() -> void;
auto isr2() -> void;
auto isr3() -> void;
auto isr4() -> void;
auto isr5() -> void;
auto isr6() -> void;
auto isr7() -> void;
auto isr8() -> void;
auto isr9() -> void;
auto isr10() -> void;
auto isr11() -> void;
auto isr12() -> void;
auto isr13() -> void;
auto isr14() -> void;
auto isr15() -> void;
auto isr16() -> void;
auto isr17() -> void;
auto isr18() -> void;
auto isr19() -> void;
auto isr20() -> void;
auto isr21() -> void;
auto isr22() -> void;
auto isr23() -> void;
auto isr24() -> void;
auto isr25() -> void;
auto isr26() -> void;
auto isr27() -> void;
auto isr28() -> void;
auto isr29() -> void;
auto isr30() -> void;
auto isr31() -> void;

} // extern "C"
#endif // CONTRARY_BOOT_EXCEPTIONS_H
