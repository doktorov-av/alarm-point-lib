cmake_minimum_required(VERSION 3.20)
enable_testing()

find_package(GTest REQUIRED)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp")

add_executable(tests-all ${src} ${hdr})
target_link_libraries(tests-all PRIVATE gtest::gtest alarm-point-lib)
target_include_directories(tests-all PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)