FIND_PACKAGE(Catch2 3 REQUIRED)
FIND_PACKAGE(trompeloeil REQUIRED)

INCLUDE(Catch)

MACRO(ADD_TEST_EXECUTABLE __target)
    IF (${ARGC} LESS 2)
        MESSAGE(FATAL_ERROR "ADD_TEST_EXECUTABLE: No sources provided for test executable ${__target}")
    ENDIF ()

    SET(SOURCES ${ARGV})
    LIST(POP_FRONT SOURCES)
    ADD_EXECUTABLE(${__target}
                   tests-main.cpp
                   ${SOURCES}
    )

    TARGET_INCLUDE_DIRECTORIES(${__target}
                               PRIVATE
                               ${PROJECT_SOURCE_DIR}/include)
    TARGET_LINK_LIBRARIES(${__target}
                          Catch2::Catch2
                          fmt
                          trompeloeil::trompeloeil
    )
    CATCH_DISCOVER_TESTS(${__target})

ENDMACRO()

ADD_TEST_EXECUTABLE(enum-utils-tests
                    enum-utils/test-enum-utils.cpp
)
