add_library(murph_geometry)

target_sources(murph_geometry
    PUBLIC FILE_SET CXX_MODULES FILES
    geometry.cppm
    geometrymodel.cppm
    )

target_sources(murph_geometry
    PRIVATE
    geometrymodel.cpp
    )

target_link_libraries(murph_geometry PRIVATE murph_utils murph_math)