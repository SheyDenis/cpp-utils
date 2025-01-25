FIND_PACKAGE(Catch2 3 REQUIRED)
FIND_PACKAGE(trompeloeil REQUIRED)

INCLUDE(Catch)

MACRO(ADD_TEST_EXECUTABLE)
    CMAKE_PARSE_ARGUMENTS(TEST_EXECUTABLE
                          ""
                          "NAME"
                          "SOURCES;LINK_LIBRARIES"
                          ${ARGN}
    )
    IF (NOT DEFINED TEST_EXECUTABLE_NAME)
        MESSAGE(FATAL_ERROR "ADD_TEST_EXECUTABLE: No name provided for test executable.")
    ENDIF ()
    IF (NOT DEFINED TEST_EXECUTABLE_SOURCES)
        MESSAGE(FATAL_ERROR "ADD_TEST_EXECUTABLE: No sources provided for test executable ${TEST_EXECUTABLE_NAME}")
    ENDIF ()

    ADD_EXECUTABLE(${TEST_EXECUTABLE_NAME} ${TEST_EXECUTABLE_SOURCES} tests-main.cpp)

    TARGET_LINK_LIBRARIES(${TEST_EXECUTABLE_NAME}
                          PRIVATE
                          Catch2::Catch2
                          fmt::fmt
                          trompeloeil::trompeloeil
                          ${TEST_EXECUTABLE_LINK_LIBRARIES}
    )
    CATCH_DISCOVER_TESTS(${TEST_EXECUTABLE_NAME})
ENDMACRO()

ADD_TEST_EXECUTABLE(NAME enum-utils-tests
                    SOURCES
                    enum-utils/test-enum-map.cpp
                    enum-utils/test-enum-utils.cpp
                    LINK_LIBRARIES
                    cpp-utils::enum-utils
)
SET_CMAKE_TARGET_PROPERTIES(TARGET enum-utils-tests)
SET_COMPILER_WARNING_FLAGS(TARGET enum-utils-tests)
