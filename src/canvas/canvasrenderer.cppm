// PURPOSE: Define the low level renderer api.
//
// CLASSES:
//  PrimitiveRenderer: define low level render api.
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

// This class implements the low level primitives to draw pixels on a buffer.
// The Context data must be always non null and it is responsability of the caller to
// ensure this precondition.
export class PrimitiveRenderer {
public:
    explicit constexpr PrimitiveRenderer(Context& context_) : context{context_} {}

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
    

public:
    Context& context;
};
    
} // namespace murph::canvas 
