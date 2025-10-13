module murph.geometry.model;


namespace murph::geometry {

Mesh::Mesh(std::filesystem::path filename) {
    std::ifstream file{filename};     
    if (!file) {
        throw std::runtime_error("error while opening the file.");
    }

    std::stringstream filedata;
    filedata << file.rdbuf();
    file.close();

    // A better approach is to use std::from_chars (which operats directly on the string).
    // This code is shit, it's only for temporary tests of loading files and visualize them.
    const std::string_view delim{" "};
    for (std::string line; std::getline(filedata, line);) {
        if (line.starts_with("v ")) {
            auto text_data = std::string_view{line.data() + 2};
            std::array<f32, 3> v;
            u32 i = 0;
            for (const auto num : text_data | std::views::split(delim) | std::ranges::to<std::vector<std::string>>()) {
                v[i++] = std::stof(num);
            }
            vertices.emplace_back(v[0], v[1], v[2], 1);
        } else if (line.starts_with("f ")) {
            auto text_data = std::string_view{line.data() + 2};
            std::array<u32, 3> v;
            u32 i = 0;
            const std::string_view delim2{"/"};
            for (const auto s : text_data | std::views::split(delim) | std::ranges::to<std::vector<std::string>>()) {
                // Split again on /
                for (const auto num : s | std::views::split(delim2) | std::ranges::to<std::vector<std::string>>()) {
                    v[i++] = std::stoul(num) - 1;
                    // We need only the first one.
                    break;
                }
            }
            triangles.emplace_back(std::array<u32, 3>{v[0], v[1], v[2]});
        }
    }

}
    
} // namespace murph::geometry
