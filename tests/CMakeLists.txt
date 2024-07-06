FIND_PACKAGE(Catch2 3 REQUIRED)
FIND_PACKAGE(trompeloeil REQUIRED)

ADD_EXECUTABLE(dummy-tests
               tests_main.cpp
               dummy/test_dummy.cpp
)
TARGET_LINK_LIBRARIES(dummy-tests
                      dummy-lib

                      Catch2::Catch2
                      trompeloeil::trompeloeil
)

INCLUDE(Catch)
CATCH_DISCOVER_TESTS(dummy-tests)
