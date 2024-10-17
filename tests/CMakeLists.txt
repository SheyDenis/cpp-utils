FIND_PACKAGE(Catch2 3 REQUIRED)
FIND_PACKAGE(trompeloeil REQUIRED)

ADD_EXECUTABLE(enum-utils-tests
               tests-main.cpp
               enum-utils/test-enum-utils.cpp
)
TARGET_INCLUDE_DIRECTORIES(enum-utils-tests
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include)
TARGET_LINK_LIBRARIES(enum-utils-tests
                      Catch2::Catch2
                      trompeloeil::trompeloeil
)

INCLUDE(Catch)
CATCH_DISCOVER_TESTS(enum-utils-tests)
