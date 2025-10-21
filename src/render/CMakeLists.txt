add_library(murph_render)

target_sources(murph_render
    PUBLIC FILE_SET CXX_MODULES FILES
    render.cppm
    rendercamera.cppm
    )

target_link_libraries(murph_render PRIVATE murph_utils murph_math)