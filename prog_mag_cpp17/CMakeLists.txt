cmake_minimum_required(VERSION 2.8)
project(benchmarks_prog_mag_cpp17)

set(CELERO_DIR /path/to/Celero)
set(RANGE_DIR /path/to/range-v3)

add_subdirectory(${CELERO_DIR} ./celero-build)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -finline-limit=250 -O2 -fno-lto")

include_directories(
    ${CELERO_DIR}/include
    ${RANGE_DIR}/include
)

if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/string_ref_data.hpp")
    set(NO_DATA TRUE)
endif()

if (${NO_DATA})
    message(FATAL_ERROR "Data not generated. Please use generate_data.py script before building.")
endif()

set_source_files_properties(string_ref_bench.cpp PROPERTIES COMPILE_FLAGS -std=c++14)
add_executable(string_ref_bench string_ref_bench.cpp)
target_link_libraries(string_ref_bench celero)

add_executable(sort_bench sort_bench.cpp)
target_link_libraries(sort_bench celero)
