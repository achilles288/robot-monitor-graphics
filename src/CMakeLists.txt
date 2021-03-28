set(RMGCONFIG_RESOURCE_PATH ${PROJECT_SOURCE_DIR}/share)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h
)

FILE(COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h
    DESTINATION ${CMAKE_BINARY_DIR}/include/rmg
)

add_subdirectory(base)
add_subdirectory(window)

if(wxWidgets_FOUND)
add_subdirectory(wx)
endif()