find_package(
    Doxygen
    REQUIRED dot
)

set(DOXYGEN_PROJECT_NAME "Robot Monitor Graphics")
set(DOXYGEN_PROJECT_LOGO images/logo_header.svg)

set(DOXYGEN_PROJECT_BRIEF
    "Simple and quick 2D/3D graphics engine for simulation")

set(DOXYGEN_ALIASES
    license{1}=\"<dl class='section copyright'>
                   <dt>License</dt>
                   <dd>\\1 </dd>
                 </dl>\"
)

set(DOXYGEN_QUIET YES)
set(DOXYGEN_IMAGE_PATH images)
set(DOXYGEN_EXAMPLE_PATH example)
set(DOXYGEN_EXAMPLE_RECURSIVE YES)
set(DOXYGEN_STRIP_FROM_PATH ${CMAKE_BINARY_DIR}/include)

set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYGEN_HTML_OUTPUT api)
set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_COLLABORATION_GRAPH NO)
set(DOXYGEN_INCLUDE_GRAPH NO)
set(DOXYGEN_INCLUDED_BY_GRAPH NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)

set(DOXYGEN_HTML_EXTRA_STYLESHEET pages/api/style.css)
set(DOXYGEN_HTML_HEADER pages/api/header.html)
set(DOXYGEN_HTML_FOOTER pages/api/footer.html)


set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_LATEX_OUTPUT ${CMAKE_BINARY_DIR}/docs/latex)
set(DOXYGEN_EXTRA_PACKAGES amsmath)


file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/docs)


doxygen_add_docs(
    doxygen
    ${CMAKE_BINARY_DIR}/include
    ${PROJECT_SOURCE_DIR}/docs/pages/api/main.dox
    ${PROJECT_SOURCE_DIR}/docs/pages/api/install.dox
    ${PROJECT_SOURCE_DIR}/docs/pages/api/getting_started.dox
    ${PROJECT_SOURCE_DIR}/docs/pages/api/transform.dox
    ${PROJECT_SOURCE_DIR}/docs/pages/api/lighting.dox
    ${PROJECT_SOURCE_DIR}/docs/pages/api
    COMMENT "Generate RMGraphics API documentation"
)

set_target_properties(doxygen PROPERTIES FOLDER ${PROJECT_NAME})
