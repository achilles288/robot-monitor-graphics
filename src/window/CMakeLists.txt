
add_library(rmgwindow SHARED
    window.cpp
    rmg/window.hpp
    rmg/internal/window_callback.hpp
)




target_include_directories(rmgwindow PUBLIC
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(rmgwindow PUBLIC
    ${GLFW_LIBRARIES}
    rmgbase
)

set_target_properties(rmgwindow PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)