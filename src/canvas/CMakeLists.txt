add_library(murph_canvas)
target_sources(murph_canvas
    PUBLIC FILE_SET CXX_MODULES FILES
    canvas.cppm
    canvascontext.cppm
    canvasrenderer.cppm
    canvaspixel.cppm
    )

# target_sources(canvas
#     PUBLIC FILES
 
#     )


target_link_libraries(murph_canvas PRIVATE murph_utils)