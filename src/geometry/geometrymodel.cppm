// PURPOSE:
//
// CLASSES:
//
// DESCRIPTION:
//
//

export module murph.geometry.model;

import std;

import murph.types;
import murph.math;

namespace murph::geometry {    

using namespace murph::math;

export class Mesh {
public:
    /// @brief  Create a mesh by loading it from a file.
    /// @param filename The name of the file.
    explicit Mesh(std::filesystem::path filename);

    /// @brief Create a mesh using the paramaters passed.
    /// @param vertices Vertices of the mesh.
    /// @param triangles Triple of indices indicating the faces of a triangle. Each index refer to the vertices vector.
    explicit Mesh(std::vector<Vec4df> vertices, std::vector<std::array<u32, 3>> triangles);

    [[nodiscard]]
    auto Vertices() const noexcept -> const std::vector<Vec4df>& {
        return vertices;
    }

    [[nodiscard]]
    auto TriangleIndices() const noexcept -> const std::vector<std::array<u32, 3>>& {
        return triangles;
    }

private:
    std::vector<Vec4df> vertices;
    std::vector<std::array<u32, 3>> triangles;
};

} // namespace murph::geometry
