cmake_minimum_required (VERSION 3.15)
project (algorithm-data_structure)

aux_source_directory(./src DIR_SRCS)
include_directories(./include)

add_compile_options(-Wall -g --std=c++17 -static)

link_directories("${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")
add_executable(test ${DIR_SRCS})
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_link_libraries(test gtest_maind gtestd)
else()
    target_link_libraries(test gtest_main gtest)
endif()