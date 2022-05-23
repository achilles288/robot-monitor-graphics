add_executable(systest_wxcanvas
    app.rc
    myglcanvas.cpp
    myglcanvas.h
    wxglade_out.cpp
    wxglade_out.h
)

target_compile_definitions(systest_wxcanvas PUBLIC
    ${RMGRAPHICS_DEFINITIONS}
)
