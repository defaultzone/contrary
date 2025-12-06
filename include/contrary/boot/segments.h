#ifndef CONTRARY_BOOT_SEGMENTS
#define CONTRARY_BOOT_SEGMENTS

#include <cstdint>

namespace contrary::boot {

using segment_selector_t = std::uint16_t;

namespace segment_selectors {

static constexpr segment_selector_t code = 0x08;

} // namespace segment_selectors
} // namespace contrary::boot

#endif // CONTRARY_BOOT_SEGMENTS
