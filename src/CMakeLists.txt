add_library(murph)
target_sources(murph
    PUBLIC FILE_SET CXX_MODULES FILES
    murph.cppm)


add_subdirectory(canvas)