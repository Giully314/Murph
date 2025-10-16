// PURPOSE: Define pixel colors.
//
// CLASSES:
//
// DESCRIPTION:
//
// USAGE:
//
export module murph.canvas.pixel;

import std;

import murph.types;

export namespace murph::canvas {

// This struct represent a pixel in the buffer.   
struct Pixel {
    explicit constexpr Pixel() = default;

    explicit constexpr Pixel(const u32 color) : 
        b{static_cast<u8>(color >> 8 & 0xff)},
        r{static_cast<u8>(color >> 24 & 0xff)}, 
        g{static_cast<u8>(color >> 16 & 0xff)},
        a{static_cast<u8>(color >> 0 & 0xff)} {} 

    explicit constexpr Pixel(const u8 b_, const u8 g_, const u8 r_, const u8 a_) : 
        b{b_},
        g{g_},
        r{r_}, 
        a{a_} {}

    constexpr auto operator+=(const Pixel rhs) -> Pixel& {
        b += rhs.b;
        g += rhs.g;
        r += rhs.r;

        return *this;
    }

    /// @brief Multiply the bgr by a constant. Alpha is not affected.
    /// @pre The constant must be >= 0.
    /// @tparam T Unsigned or float.
    /// @param c
    /// @return 
    template <typename T>
        requires std::unsigned_integral<T> || std::floating_point<T>
    constexpr auto operator*=(const T c) -> Pixel& {
        b = static_cast<u8>(b * c);
        g = static_cast<u8>(g * c);
        r = static_cast<u8>(r * c);

        return *this;
    }

    u8 b{0};
    u8 g{0};
    u8 r{0};
    u8 a{255};
};  


[[nodiscard]]
constexpr auto operator+(Pixel lhs, const Pixel rhs) -> Pixel {
    lhs += rhs;
    return lhs;
}

template <typename T>
    requires std::unsigned_integral<T> || std::floating_point<T>
[[nodiscard]]
constexpr auto operator*(Pixel lhs, const T c) -> Pixel {
    lhs *= c;
    return lhs;
}

template <typename T>
    requires std::unsigned_integral<T> || std::floating_point<T>
[[nodiscard]]
constexpr auto operator*(const T c, Pixel rhs) -> Pixel {
    rhs *= c;
    return rhs;
}


inline constexpr Pixel white {255_u8, 255_u8, 255_u8, 255_u8};
inline constexpr Pixel black {0_u8, 0_u8, 0_u8, 255_u8};
inline constexpr Pixel red {0_u8, 0_u8, 255_u8, 255_u8};
inline constexpr Pixel blue {255_u8, 0_u8, 0_u8, 255_u8};
inline constexpr Pixel green {0_u8, 255_u8, 0_u8, 255_u8};



} // namespace murph::canvas
