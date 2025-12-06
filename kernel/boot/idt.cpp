#include <contrary/boot/idt.h>
#include <contrary/boot/segments.h>
#include <contrary/boot/exceptions.h>

auto contrary::boot::idt::initialize() -> void {
    ptr_t idt_ptr = { .limit = total_idt_entries * sizeof(entry_t) - 1,
                      .base = reinterpret_cast<std::uintptr_t>(&entries[0]) };

    set_isr(0x00, reinterpret_cast<std::uintptr_t>(isr0), isr_flags);
    set_isr(0x00, reinterpret_cast<std::uintptr_t>(isr0), isr_flags);
    set_isr(0x01, reinterpret_cast<std::uintptr_t>(isr1), isr_flags);
    set_isr(0x02, reinterpret_cast<std::uintptr_t>(isr2), isr_flags);
    set_isr(0x03, reinterpret_cast<std::uintptr_t>(isr3), isr_flags);
    set_isr(0x04, reinterpret_cast<std::uintptr_t>(isr4), isr_flags);
    set_isr(0x05, reinterpret_cast<std::uintptr_t>(isr5), isr_flags);
    set_isr(0x06, reinterpret_cast<std::uintptr_t>(isr6), isr_flags);
    set_isr(0x07, reinterpret_cast<std::uintptr_t>(isr7), isr_flags);
    set_isr(0x08, reinterpret_cast<std::uintptr_t>(isr8), isr_flags);
    set_isr(0x09, reinterpret_cast<std::uintptr_t>(isr9), isr_flags);
    set_isr(0x0A, reinterpret_cast<std::uintptr_t>(isr10), isr_flags);
    set_isr(0x0B, reinterpret_cast<std::uintptr_t>(isr11), isr_flags);
    set_isr(0x0C, reinterpret_cast<std::uintptr_t>(isr12), isr_flags);
    set_isr(0x0D, reinterpret_cast<std::uintptr_t>(isr13), isr_flags);
    set_isr(0x0E, reinterpret_cast<std::uintptr_t>(isr14), isr_flags);
    set_isr(0x0F, reinterpret_cast<std::uintptr_t>(isr15), isr_flags);
    set_isr(0x10, reinterpret_cast<std::uintptr_t>(isr16), isr_flags);
    set_isr(0x11, reinterpret_cast<std::uintptr_t>(isr17), isr_flags);
    set_isr(0x12, reinterpret_cast<std::uintptr_t>(isr18), isr_flags);
    set_isr(0x13, reinterpret_cast<std::uintptr_t>(isr19), isr_flags);
    set_isr(0x14, reinterpret_cast<std::uintptr_t>(isr20), isr_flags);
    set_isr(0x15, reinterpret_cast<std::uintptr_t>(isr21), isr_flags);
    set_isr(0x16, reinterpret_cast<std::uintptr_t>(isr22), isr_flags);
    set_isr(0x17, reinterpret_cast<std::uintptr_t>(isr23), isr_flags);
    set_isr(0x18, reinterpret_cast<std::uintptr_t>(isr24), isr_flags);
    set_isr(0x19, reinterpret_cast<std::uintptr_t>(isr25), isr_flags);
    set_isr(0x1A, reinterpret_cast<std::uintptr_t>(isr26), isr_flags);
    set_isr(0x1B, reinterpret_cast<std::uintptr_t>(isr27), isr_flags);
    set_isr(0x1C, reinterpret_cast<std::uintptr_t>(isr28), isr_flags);
    set_isr(0x1D, reinterpret_cast<std::uintptr_t>(isr29), isr_flags);
    set_isr(0x1E, reinterpret_cast<std::uintptr_t>(isr30), isr_flags);
    set_isr(0x1F, reinterpret_cast<std::uintptr_t>(isr31), isr_flags);

    asm volatile("lidt %0" :: "m" (idt_ptr));
    asm volatile("sti");
}

auto contrary::boot::idt::set_isr(std::uint8_t vector_number, std::uintptr_t handler, std::uint8_t flags) -> void {
    entry_t* entry = &entries[vector_number];
    entry->offset_low = handler & 0xFFFF;
    entry->segment_selector = segment_selectors::code;
    entry->ist = entry->reserved = 0;
    entry->flags = flags;
    entry->offset_mid = (handler >> 16) & 0xFFFF;
    entry->offset_high = (handler >> 32) & 0xFFFFFFFF;
}

auto initialize_idt() -> void {
    contrary::boot::idt::initialize();
}
