# 
# Window system
# 
add_executable(systest_window window/window.cpp)

target_compile_definitions(systest_window PUBLIC
    ${RMGRAPHICS_DEFINITIONS}
)


# 
# wxCanvas system
# 
if(${wxWidgets_FOUND})
add_executable(systest_wxcanvas
    wxcanvas/myglcanvas.cpp
    wxcanvas/myglcanvas.h
    wxcanvas/wxglade_out.cpp
    wxcanvas/wxglade_out.h
)

target_compile_definitions(systest_wxcanvas PUBLIC
    ${RMGRAPHICS_DEFINITIONS}
)
endif()
