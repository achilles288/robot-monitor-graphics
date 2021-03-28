add_library(rmgwx SHARED
    wxcanvas.cpp
    wxcanvas.hpp
)

target_compile_definitions(rmgwx PUBLIC ${wxWidgets_DEFINITIONS})

file(COPY
    wxcanvas.hpp
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg
)




target_include_directories(rmgwx PUBLIC
    ${GLEW_INCLUDE_DIRS}
    ${wxWidgets_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/include
)

target_link_libraries(rmgwx PUBLIC
    ${wxWidgets_LIBRARIES}
    rmgbase
)

set_target_properties(rmgwx PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)