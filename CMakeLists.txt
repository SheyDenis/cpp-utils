CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(cpp-utils VERSION 0.0.1 LANGUAGES CXX)

INCLUDE(GNUInstallDirs)


SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)
INCLUDE(cmake-utils)

FIND_PACKAGE(fmt REQUIRED)
FIND_PACKAGE(spdlog REQUIRED)

# Start dummy-lib
ADD_LIBRARY(dummy-lib STATIC
            src/dummy/dummy.cpp
)
SET_CMAKE_TARGET_PROPERTIES(dummy-lib)

TARGET_INCLUDE_DIRECTORIES(dummy-lib
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES(dummy-lib
                      fmt::fmt
)

TARGET_COMPILE_OPTIONS(dummy-lib
                       PRIVATE
                       ${DEFAULT_COMPILER_WARNING_FLAGS}
)

ADD_EXECUTABLE(dummy
               src/dummy/main.cpp
)
TARGET_LINK_LIBRARIES(dummy
                      dummy-lib
)
# End dummy-lib

IF (NOT DISABLE_TESTS)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
ENDIF ()
