add_library(murph_math)

target_sources(murph_math
    PUBLIC FILE_SET CXX_MODULES FILES
    math_concepts.cppm math_functions.cppm 
    math_mat2d.cppm math_mat3d.cppm math_mat4d.cppm math_matrix.cppm
    math_vec2d.cppm math_vec3d.cppm math_vec4d.cppm math_vector.cppm
    math.cppm
    )

target_link_libraries(murph_math PRIVATE murph_utils)