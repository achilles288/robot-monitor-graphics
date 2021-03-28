
add_library(rmgwindow SHARED
    window.cpp
    window.hpp
    internal/window_callback.hpp
)

file(COPY
    window.hpp
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg
)

file(COPY
    internal/window_callback.hpp
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg/internal
)




target_include_directories(rmgwindow PUBLIC
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(rmgwindow PUBLIC
    ${GLFW_LIBRARIES}
    rmgbase
)

set_target_properties(rmgwindow PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)