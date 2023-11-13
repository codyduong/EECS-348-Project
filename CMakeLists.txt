cmake_minimum_required(VERSION 3.14)
project(expression_parser)

include_directories(${GTEST_INCLUDE_DIRS})

# Configure Options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure Main CLI
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

add_executable(expression_parser ${SOURCES} ${HEADERS})

# Configure Test Executable
file(GLOB TSOURCES "tests/*.cpp")
file(GLOB THEADERS "tests/*.h")

# https://google.github.io/googletest/quickstart-cmake.html

# this is not working, just install manually
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   # Specify the commit you depend on and update it regularly.
#   URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
# )
# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)


# find_package(GTest REQUIRED)

# # add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# # Now simply link against gtest or gtest_main as needed. Eg
# add_executable(tests ${TSOURCES} ${THEADERS} ${SOURCES} ${HEADERS})
# target_link_libraries(tests GTest::GTest GTest::Main)
