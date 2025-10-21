// PURPOSE: Define the buffer where the pixels are drawn.
//
// CLASSES:
//  Context: Context buffer class which represents the pixels on the screen.
//
// DESCRIPTION:
//  This module provides the atom of the canvas package, defining the Context class which is used by the renderer
//  to hold the pixel information needed to be displayed on the screen. The buffer has the (0, 0) origin in the upper left.
//
// USAGE:
//

export module murph.canvas.context;

import std;

import murph.types;
import murph.canvas.pixel;

namespace murph::canvas {

/// @brief This class represents a context rendering object used to hold pixels.
export class Context {
public:

    /// @brief Construct a context with the specified width and height.
    /// @param width_ Width of the context.
    /// @param height_ Height of the context.
    explicit constexpr Context(const u32 width_, const u32 height_) : 
        screen_buffer{std::make_unique<Pixel[]>(width_ * height_)}, zbuffer{std::make_unique<f32[]>(width_ * height_)},
        width{width_},
        height{height_} { }


    /// @brief Access the pixel at row (y) i and column (x) j. 
    /// Note that this access pattern implies that the coordinate system used by the context has the origin to the 
    /// upper left of the 2d buffer. 
    /// @pre The indices i and j are valid with respect to the dimension of the buffer.
    /// @param i 
    /// @param j 
    /// @return The Pixel at the coordinate.
    template <typename Self>
    [[nodiscard]] constexpr auto&& operator[](this Self&& self, const u32 i, const u32 j) {
        return std::forward<Self>(self).screen_buffer[i * self.width + j];
    }

    /// @brief Get the underlying buffer.
    /// The buffer has an internal order of b g r a for representing a single pixel (using 32bit).
    /// @return Return a void* to the buffer. 
    [[nodiscard]]
    constexpr auto Buffer() const -> non_null_ptr<void> {
        return static_cast<void*>(screen_buffer.get());
    }

    /// @brief Access the value of the zbuffer at row i and column j.
    /// @pre Indices must be in a valid range.
    /// @param i 
    /// @param j 
    /// @return 
    [[nodiscard]]
    constexpr auto ZBuffer(const u32 i, const u32 j) const -> f32 {
        return zbuffer[i * width + j];
    }

    /// @brief Set the value of the zbuffer at row i and column j.
    /// @param i 
    /// @param j 
    /// @param c 
    constexpr auto ZBuffer(u32 i, u32 j, const f32 c) -> void {
        zbuffer[i * width + j] = c;
    }

    /// @brief Get the width of the context.
    /// @return unsigned representing the width.
    [[nodiscard]]
    constexpr auto Width() const -> u32 {
        return width;
    }

    /// @brief Get the height of the context.
    /// @return unsigned representing the height.    
    [[nodiscard]]
    constexpr auto Height() const -> u32 {
        return height;
    }

    [[nodiscard]]
    constexpr auto ZBufferPtr() const -> non_null_ptr<void> {
        return static_cast<void*>(zbuffer.get());
    }

private:
    std::unique_ptr<Pixel[]> screen_buffer;
    std::unique_ptr<f32[]> zbuffer;
    u32 width;
    u32 height;
};


} // namespace murph::canvas
    
