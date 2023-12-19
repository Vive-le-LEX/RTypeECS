
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)

    add_custom_target( doc_doxygen ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND git clone git@github.com:jothepro/doxygen-awesome-css.git
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/docs/.nojekyll
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
