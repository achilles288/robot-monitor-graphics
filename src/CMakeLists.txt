set(RMGCONFIG_RESOURCE_PATH ${PROJECT_SOURCE_DIR}/share)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/config/rmg/config.h
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/window
    ${CMAKE_CURRENT_SOURCE_DIR}/wx
)

add_subdirectory(base)
add_subdirectory(window)

if(wxWidgets_FOUND)
add_subdirectory(wx)
endif()
