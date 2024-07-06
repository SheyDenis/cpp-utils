CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(cpp-utils CXX)

INCLUDE(GNUInstallDirs)


SET(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)
INCLUDE(cmake-utils)

FIND_PACKAGE(fmt REQUIRED)
FIND_PACKAGE(spdlog REQUIRED)

ADD_EXECUTABLE(dummy
               src/dummy/main.cpp
)
SET_CMAKE_TARGET_PROPERTIES(dummy)

TARGET_INCLUDE_DIRECTORIES(dummy
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include
)

TARGET_LINK_LIBRARIES(dummy
                      fmt::fmt
)

TARGET_COMPILE_OPTIONS(dummy
                       PRIVATE
                       ${DEFAULT_COMPILER_WARNING_FLAGS}
)
