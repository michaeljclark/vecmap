cmake_minimum_required(VERSION 3.0)

project(vecmap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

enable_testing()

add_executable(bench_map tests/bench_map.cc)
add_executable(test_map tests/test_map.cc)
add_test(TEST_MAP test_map)

add_executable(perf_vecmap tests/perf_map.cc)
target_compile_definitions(perf_vecmap PRIVATE VECMAP=1)

add_executable(perf_stdmap tests/perf_map.cc)
target_compile_definitions(perf_stdmap PRIVATE STDMAP=1)