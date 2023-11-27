cmake_minimum_required(VERSION 3.14)
project(expression_parser)

include_directories(${GTEST_INCLUDE_DIRS})

# Configure Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Main CLI
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(expression_parser ${SOURCES} src/version.hpp ${HEADERS})

# Remove main.cpp for test runners
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Configure Test Executable
file(GLOB TSOURCES "tests/*.cpp")
file(GLOB THEADERS "tests/*.h")

# https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests ${TSOURCES} ${SOURCES})
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
