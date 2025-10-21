// PURPOSE: 
//
// CLASSES:
//
// DESCRIPTION:  
// 
// USAGE:
//

export module murph.render.camera;

import murph.math;
import murph.types;

namespace murph::render {


export class Camera {
public:
    constexpr Camera() = default;

    constexpr Camera(const math::Vec3df& position_) : position(position_) {}

    /// @brief Compute the view matrix.
    /// @return 
    [[nodiscard]]
    constexpr auto View(const math::Vec3df& center, const math::Vec3df& up) const noexcept -> math::Mat4df {
        auto n = position - center;
        n.Normalize();
        auto nh = math::Vec4df{n, 0.0f};
        
        auto l = math::Product::Cross(up, n);
        l.Normalize();
        auto lh = math::Vec4df{l, 0.0f};
        
        auto m = math::Product::Cross(n, l);
        m.Normalize();
        auto mh = math::Vec4df{m, 0.0f};

        const math::Mat4df camera_center{
            math::Vec4df{1.0f, 0.0f, 0.0f, -center.x},
            math::Vec4df{0.0f, 1.0f, 0.0f, -center.y},
            math::Vec4df{0.0f, 0.0f, 1.0f, -center.z},
            math::Vec4df{0.0f, 0.0f, 0.0f, 1.0f},
        };

        // The camera matrix is orthonormal, so the inverse is the transpose (which we construct it directly).
        return math::Mat4df{lh, mh, nh, math::Vec4df{0.0f, 0.0f, 0.0f, 1.0f}} * camera_center;
    }

// private:
    math::Vec3df position;
};
    
} // namespace murph::render
