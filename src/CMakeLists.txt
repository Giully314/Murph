# This should be moved into its own dir.
add_library(murph_utils)
target_sources(murph_utils
PUBLIC FILE_SET CXX_MODULES FILES
types.cppm)

add_subdirectory(canvas)

add_library(murph)
target_sources(murph
    PUBLIC FILE_SET CXX_MODULES FILES
    murph.cppm)
target_link_libraries(murph PUBLIC murph_utils murph_canvas)