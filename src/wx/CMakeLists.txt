add_library(rmgwx SHARED
    wxcanvas.cpp
    rmg/wxcanvas.hpp
)

target_compile_definitions(rmgwx PUBLIC ${wxWidgets_DEFINITIONS})




target_include_directories(rmgwx PUBLIC
    ${GLEW_INCLUDE_DIRS}
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(rmgwx PUBLIC
    ${wxWidgets_LIBRARIES}
    rmgbase
)

set_target_properties(rmgwx PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)