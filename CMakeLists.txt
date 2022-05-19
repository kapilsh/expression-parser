cmake_minimum_required(VERSION 3.16)
project(expression_parser C CXX)

add_compile_options(
        -std=gnu++17
        -Wall
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")


include_directories(include)

file(GLOB_RECURSE SILVER_INCLUDES CONFIGURE_DEPENDS "include/*.h")
file(GLOB_RECURSE SILVER_SOURCES CONFIGURE_DEPENDS "src/silver/*.cpp")

# ================== SOURCE ============================

# SILVER LIBRARY
add_library(silver STATIC ${SILVER_INCLUDES} ${SILVER_SOURCES})

# REPL TARGET
add_executable(silver-repl src/targets/main.cpp)
target_link_libraries(silver-repl silver)

# ================== TESTS ============================
add_library(test_lib STATIC tests/catch_amalgamated.hpp tests/catch_amalgamated.cpp)

# Unit tests
add_executable(parser-tests tests/parser_tests.cpp)
target_link_libraries(parser-tests silver test_lib)

enable_testing()
add_test(NAME ParserTests COMMAND parser-tests)
add_custom_target(run_unit_test ALL
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS parser-tests)