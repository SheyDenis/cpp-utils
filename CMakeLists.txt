CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(cpp-utils VERSION 0.3.0 LANGUAGES CXX)

INCLUDE(GNUInstallDirs)

OPTION(GENERATE_DOCS "Generate project docs" ON)

SET(PROJECT_NAMESPACE ${PROJECT_NAME})
IF (NOT DEFINED CONAN_TOOLCHAIN_PATH)
    SET(CONAN_TOOLCHAIN_PATH ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake)
ENDIF (NOT DEFINED CONAN_TOOLCHAIN_PATH)
MESSAGE(STATUS "CONAN_TOOLCHAIN_PATH: ${CONAN_TOOLCHAIN_PATH}")

SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)
INCLUDE(cmake-utils)
INCLUDE(compiler-utils)
INCLUDE(${CONAN_TOOLCHAIN_PATH})

ADD_LIBRARY(enum-utils INTERFACE
            ${PROJECT_SOURCE_DIR}/include/enum-utils/enum-map.hpp
            ${PROJECT_SOURCE_DIR}/include/enum-utils/enum-utils.hpp
)
ADD_LIBRARY(${PROJECT_NAMESPACE}::enum-utils ALIAS enum-utils)
TARGET_INCLUDE_DIRECTORIES(enum-utils INTERFACE
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

IF (GENERATE_DOCS)
    # TODO - Allow disabling via conanfile.py.
    FIND_PACKAGE(Doxygen REQUIRED COMPONENTS dot doxygen)
    SET(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs)

    SET(DOXYGEN_GENERATE_HTML YES)
    SET(DOXYGEN_GENERATE_LATEX NO)
    SET(DOXYGEN_GENERATE_MAN NO)
    SET(DOXYGEN_OUTPUT_DIRECTORY ${DOCS_DIR})
    DOXYGEN_ADD_DOCS(doxygen-docs
                     ${PROJECT_SOURCE_DIR}/include
                     ${PROJECT_SOURCE_DIR}/src
                     WORKING_DIRECTORY ${DOCS_DIR}
                     COMMENT "Generating HTML documentation with Doxygen"
    )
    ADD_CUSTOM_TARGET(graph-dependencies
                      COMMAND ${CMAKE_COMMAND} . --graphviz=dependencies_graph.dot
                      COMMAND ${DOXYGEN_DOT_EXECUTABLE} -Tsvg dependencies_graph.dot -o ${DOCS_DIR}/dependencies_graph.svg
                      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                      COMMENT "Generating dependencies graph with Doxygen"
    )
    ADD_CUSTOM_TARGET(generate-docs ALL
                      DEPENDS doxygen-docs graph-dependencies
    )
ENDIF (GENERATE_DOCS)

IF (NOT DISABLE_TESTS)
    FIND_PACKAGE(fmt REQUIRED)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF ()
