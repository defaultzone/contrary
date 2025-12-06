#ifndef CONTRARY_BOOT_IDT_H
#define CONTRARY_BOOT_IDT_H

#include <contrary/boot/segments.h>

namespace contrary::boot {
namespace entry_gates {

static constexpr std::uint8_t interrupt = 0xE;

constexpr auto pres(std::uint8_t x) -> std::uint8_t { return (x & 0x1) << 0x7; }
constexpr auto ring(std::uint8_t x) -> std::uint8_t { return (x & 0x3) << 0x5; }

} // namespace entry_gates

class idt final {
public:
    static constexpr std::uint16_t total_idt_entries = 256;

    struct __attribute__((packed)) entry_t final {
        std::uint16_t offset_low;
        segment_selector_t segment_selector;
        std::uint8_t ist;
        std::uint8_t flags;
        std::uint16_t offset_mid;
        std::uint32_t offset_high;
        std::uint32_t reserved;
    }; // struct __attribute__((packed)) entry_t final

    struct __attribute__((packed)) ptr_t final {
        std::uint16_t limit;
        std::uint64_t base;
    }; // struct __attribute__((packed)) ptr_t final

    static inline entry_t entries[total_idt_entries];

    static auto initialize() -> void;
private:
    static constexpr std::uint8_t isr_flags = entry_gates::pres(1) |
                                              entry_gates::ring(0) |
                                              entry_gates::interrupt;

    static auto set_isr(std::uint8_t vector_number, std::uintptr_t handler, std::uint8_t flags) -> void;
}; // class idt final

} // namespace contrary::boot

extern "C" auto initialize_idt() -> void;

#endif // CONTRARY_BOOT_IDT_H
