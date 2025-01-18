FIND_PACKAGE(Catch2 3 REQUIRED)
FIND_PACKAGE(trompeloeil REQUIRED)

INCLUDE(Catch)

MACRO(ADD_TEST_EXECUTABLE TARGET)
    IF (${ARGC} LESS 2)
        MESSAGE(FATAL_ERROR "ADD_TEST_EXECUTABLE: No sources provided for test executable ${TARGET}")
    ENDIF ()

    SET(SOURCES ${ARGV})
    LIST(POP_FRONT SOURCES)
    ADD_EXECUTABLE(${TARGET}
                   tests-main.cpp
                   ${SOURCES}
    )

    TARGET_LINK_LIBRARIES(${TARGET}
                          Catch2::Catch2
                          fmt::fmt
                          trompeloeil::trompeloeil
    )
    CATCH_DISCOVER_TESTS(${TARGET})

ENDMACRO()

ADD_TEST_EXECUTABLE(enum-utils-tests
                    enum-utils/test-enum-map.cpp
                    enum-utils/test-enum-utils.cpp
)
TARGET_LINK_LIBRARIES(enum-utils-tests cpp-utils::enum-utils)
