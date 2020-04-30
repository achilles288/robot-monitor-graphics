find_package(
    Doxygen
    REQUIRED dot
)

set(DOXYGEN_PROJECT_NAME "Robot Monitor Graphics")
set(DOXYGEN_PROJECT_LOGO ${PROJECT_SOURCE_DIR}/docs/images/logo_header.svg)

set(DOXYGEN_PROJECT_BRIEF
    "Simple and quick 2D/3D graphics engine for simulation")

set(DOXYGEN_ALIASES
    license{1}=\"<dl class='section copyright'>
                   <dt>License</dt>
                   <dd>\\1 </dd>
                 </dl>\"
)

set(DOXYGEN_QUIET YES)
set(DOXYGEN_IMAGE_PATH ${PROJECT_SOURCE_DIR}/docs/images)
set(DOXYGEN_EXAMPLE_PATH ${PROJECT_SOURCE_DIR}/example)
set(DOXYGEN_EXAMPLE_RECURSIVE YES)
set(DOXYGEN_STRIP_FROM_PATH ${PROJECT_SOURCE_DIR}/include)
set(DOXYGEN_HTML_OUTPUT ${PROJECT_SOURCE_DIR}/docs/api)
set(DOXYGEN_USE_MATHJAX YES)
set(DOXYGEN_COLLABORATION_GRAPH NO)
set(DOXYGEN_INCLUDE_GRAPH NO)
set(DOXYGEN_INCLUDED_BY_GRAPH NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)

set(DOXYGEN_HTML_EXTRA_STYLESHEET
    ${PROJECT_SOURCE_DIR}/docs/pages/api/style.css)

set(DOXYGEN_HTML_HEADER
    ${PROJECT_SOURCE_DIR}/docs/pages/api/header.html)

set(DOXYGEN_HTML_FOOTER
    ${PROJECT_SOURCE_DIR}/docs/pages/api/footer.html)


doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}/include/rmg
    ${PROJECT_SOURCE_DIR}/docs/pages/api
    COMMENT "Generate RMGraphics API documentation"
)


