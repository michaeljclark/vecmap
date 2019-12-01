cmake_minimum_required(VERSION 3.0)

project(vecmap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

enable_testing()

add_executable(bench_map tests/bench_map.cc)
add_executable(test_map tests/test_map.cc)
add_test(TEST_MAP test_map)
