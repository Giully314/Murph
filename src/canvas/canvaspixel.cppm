// PURPOSE: Define pixel colors.
//
// CLASSES:
//
// DESCRIPTION:
//
// USAGE:
//
export module murph.canvas.pixel;

import murph.types;

export namespace murph::canvas {

// This struct represent a pixel in the buffer.   
struct Pixel {
    explicit constexpr Pixel() = default;

    explicit constexpr Pixel(const u32 color) : 
        r{static_cast<u8>(color >> 24 & 0xff)}, 
        g{static_cast<u8>(color >> 16 & 0xff)},
        b{static_cast<u8>(color >> 8 & 0xff)},
        a{static_cast<u8>(color >> 0 & 0xff)} {} 

    explicit constexpr Pixel(const u8 r_, const u8 g_, const u8 b_, const u8 a_) : 
        r{r_}, 
        g{g_},
        b{b_},
        a{a_} {}

    u8 r{0};
    u8 g{0};
    u8 b{0};
    u8 a{255};
};  

inline constexpr Pixel white {255_u8, 255_u8, 255_u8, 255_u8};
inline constexpr Pixel black {0_u8, 0_u8, 0_u8, 255_u8};


} // namespace murph::canvas
