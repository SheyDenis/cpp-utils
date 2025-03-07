CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(cpp-utils VERSION 0.4.0 LANGUAGES CXX)

INCLUDE(GNUInstallDirs)

OPTION(GENERATE_DOCS "Generate project docs" ON)

FIND_PACKAGE(Python3 COMPONENTS Interpreter)
IF (NOT ${Python_FOUND})
    MESSAGE(FATAL_ERROR "Python3 not found.")
ENDIF (NOT ${Python_FOUND})

SET(PROJECT_NAMESPACE ${PROJECT_NAME})
IF (NOT DEFINED CONAN_TOOLCHAIN_PATH)
    SET(CONAN_TOOLCHAIN_PATH ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake)
ENDIF (NOT DEFINED CONAN_TOOLCHAIN_PATH)
MESSAGE(STATUS "CONAN_TOOLCHAIN_PATH: ${CONAN_TOOLCHAIN_PATH}")

IF (NOT ${CONAN_TOOLCHAIN_PATH} STREQUAL "")
    INCLUDE(${CONAN_TOOLCHAIN_PATH})
ELSE ()
    # Alternative way to find Conan supplied packages.
    LIST(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators)
ENDIF (NOT ${CONAN_TOOLCHAIN_PATH} STREQUAL "")

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
INCLUDE(cmake-utils)
INCLUDE(compiler-utils)

ADD_LIBRARY(enum-utils INTERFACE)
TARGET_INCLUDE_DIRECTORIES(enum-utils INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include/enum-utils>)
SET_CMAKE_TARGET_PROPERTIES(TARGET enum-utils)
ADD_LIBRARY(${PROJECT_NAMESPACE}::enum-utils ALIAS enum-utils)

IF (GENERATE_DOCS)
    # TODO - Allow disabling via conanfile.py.
    FIND_PACKAGE(Doxygen REQUIRED COMPONENTS dot doxygen)
    SET(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs)
    IF (NOT EXISTS ${DOCS_DIR})
        FILE(MAKE_DIRECTORY ${DOCS_DIR})
    ENDIF (NOT EXISTS ${DOCS_DIR})

    SET(DOXYGEN_EXTRACT_STATIC YES)
    SET(DOXYGEN_GENERATE_HTML YES)
    SET(DOXYGEN_GENERATE_LATEX NO)
    SET(DOXYGEN_GENERATE_MAN NO)
    SET(DOXYGEN_OUTPUT_DIRECTORY ${DOCS_DIR})
    SET(DOXYGEN_OUTPUT_LANGUAGE English)
    SET(DOXYGEN_STRIP_FROM_PATH ${CMAKE_SOURCE_DIR}/include)
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
    ADD_CUSTOM_TARGET(generate-docs
                      DEPENDS doxygen-docs graph-dependencies
    )
ENDIF (GENERATE_DOCS)

IF (NOT DISABLE_TESTS)
    FIND_PACKAGE(fmt REQUIRED)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF ()
