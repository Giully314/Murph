// PURPOSE: Define the low level renderer api.
//
// CLASSES:
//  PrimitiveRenderer: Implements the low level render API.
//
// DESCRIPTION:
//  This module defines the low level api (line, tringle, ...) on a Context data.
//
// USAGE:
//
//


export module murph.canvas.renderer;

import std;

import murph.types;
import murph.canvas.context;
import murph.canvas.pixel;

namespace murph::canvas {

/// @brief This class implements the low level primitives to draw pixels on a buffer.
/// The Context data must be always non null and it is responsability of the caller to
/// ensure this precondition.
export class PrimitiveRenderer {
public:

    /// @brief Construct a renderer.
    /// @pre The context must outlive this object.
    /// @param context_ 
    explicit constexpr PrimitiveRenderer(Context& context_) : context{context_} {}

    /// @brief Draw a line between two points.
    /// @param x1 
    /// @param y1 
    /// @param x2 
    /// @param y2 
    /// @param color 
    /// @return 
    constexpr auto DrawLine(i32 x1, i32 y1, i32 x2, i32 y2, const Pixel color) -> void {
        // TODO: Add check on boundaries. 

        const bool steep = std::abs(x1 - x2) < std::abs(y1 - y2);
        if (steep) {
            std::swap(x1, y1);
            std::swap(x2, y2);
        }

        if (x1 > x2) {
            std::swap(x1, x2);
            std::swap(y1, y2);
        }

        const f32 length = x2-x1;
        const f32 height = y2 - y1;
        const f32 lh = height / length;
        f32 y = y1;

        if (steep) {
            for (u32 x = static_cast<u32>(x1); x <= static_cast<u32>(x2); ++x) {
                context[x, static_cast<u32>(y)] = color;
                y += lh;
            } 
        } else {
            for (u32 x = static_cast<u32>(x1); x <= static_cast<u32>(x2); ++x) {
                context[static_cast<u32>(y), x] = color;
                y += lh;
            }
        }
    }

    /// @brief Draw a triangle with the specified color.
    /// @param x1 
    /// @param y1 
    /// @param x2 
    /// @param y2 
    /// @param x3 
    /// @param y3 
    /// @param color
    /// @return 
    constexpr auto DrawTriangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, const Pixel color) -> void {
        DrawLine(x1, y1, x2, y2, color);
        DrawLine(x1, y1, x3, y3, color);
        DrawLine(x2, y2, x3, y3, color);
    }
    
    /// @brief Fill a triangle with the specifed color. 
    /// @pre The points must be in counter clockwise order.
    /// @param x1 
    /// @param y1 
    /// @param x2 
    /// @param y2 
    /// @param x3 
    /// @param y3 
    /// @param color 
    constexpr auto FillTriangle(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, const Pixel color) -> void {
        const auto bminx = std::min({x1, x2, x3});
        const auto bminy = std::min({y1, y2, y3});
        const auto bmaxx = std::max({x1, x2, x3});
        const auto bmaxy = std::max({y1, y2, y3});
        const auto double_total_area = SignedTriangleDoubleArea(x1, y1, x2, y2, x3, y3);
        
        // If the area is less than 1, we can skip the rasterization because it is too small in this case.
        if (double_total_area < 1) return;
        
        // This loop can be parallelized.
        for (auto y = bminy; y <= bmaxy; ++y) {
            for (auto x = bminx; x <= bmaxx; ++x) {
                const auto alpha = SignedTriangleDoubleArea(x, y, x2, y2, x3, y3);
                const auto beta = SignedTriangleDoubleArea(x, y, x3, y3, x1, y1) ;
                const auto gamma = SignedTriangleDoubleArea(x, y, x1, y1, x2, y2);
                if (alpha < 0.0f || beta < 0.0f || gamma < 0.0f) continue; 
                
                context[y, x] = color;
            }
        } 
    }


public:
    Context& context;

private:
    /// @brief Compute the double signed area of a triangle using Shoelase formula.
    /// @pre The points must be in counter clockwise order.
    /// @param x1 
    /// @param y1 
    /// @param x2 
    /// @param y2 
    /// @param x3 
    /// @param y3 
    /// @return Double the area.
    [[nodiscard]]
    constexpr auto SignedTriangleDoubleArea(
        const i32 x1, const i32 y1, 
        const i32 x2, const i32 y2, 
        const i32 x3, const i32 y3) 
            const -> f32 {
        // This should be multiplies by 0.5f to get the area of the triangle, 
        // but we use this only to get the sign so the value itself doesn't matter in this context.
        return static_cast<f32>((y2 - y1) * (x2 + x1) + (y3 - y2) * (x3 + x2) + (y1 - y3) * (x1 + x3));
    }
};
    
} // namespace murph::canvas 
