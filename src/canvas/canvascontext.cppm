// PURPOSE:
//
// CLASSES:
//
// DESCRIPTION:
//
// USAGE:
//

export module murph.canvas.context;

import std;

import murph.types;
import murph.canvas.pixel;

namespace murph::canvas {

// This class keeps data about the buffer of pixels to be shown on the screen. 
export class Context {
public:
    explicit constexpr Context(const u32 width_, const u32 height_) : 
        screen_buffer{std::make_unique<Pixel[]>(width_ * height_)},
        width{width_},
        height{height_} { }

    // Access the pixel at row i and column j.
    template <typename Self>
    [[nodiscard]] constexpr auto&& operator[](this Self&& self, u32 i, u32 j) {
        return std::forward<Self>(self).screen_buffer[i * self.width + j];
    }

    [[nodiscard]]
    constexpr auto Buffer() const -> non_null_ptr<void> {
        return static_cast<void*>(screen_buffer.get());
    }

    [[nodiscard]]
    constexpr auto Width() const -> u32 {
        return width;
    }
    
    [[nodiscard]]
    constexpr auto Height() const -> u32 {
        return height;
    }

private:
    std::unique_ptr<Pixel[]> screen_buffer;
    u32 width;
    u32 height;
};


} // namespace murph::canvas
    
