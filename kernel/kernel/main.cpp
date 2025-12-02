#include <contrary/kernel/main.h>
#include <cstdint>

constexpr auto strlen(const char* text) -> std::size_t {
    std::size_t length = 0;
    
    while (*text != '\0') {
        length++;
        text++;
    }

    return length;
}

auto kernel_main() -> void {
    static constexpr const char* text = "Hello, Contrary!";
    static constexpr std::uint16_t entry_color = (0 << 4) | 7; // Light gray on black.

    auto terminal_buffer = reinterpret_cast<volatile std::uint16_t*>(0xB8000);

    for (uint8_t i = 0; i < strlen(text); i++)
        terminal_buffer[i] = text[i] | (entry_color << 8);

    while (true);
}
