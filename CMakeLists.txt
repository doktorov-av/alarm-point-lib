cmake_minimum_required(VERSION 3.16)
project(alarm-point-lib VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp")

add_executable(alarm-point-lib ${src} ${hdr})
target_include_directories(alarm-point-lib PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions( alarm-point-lib PRIVATE
        "APL_NAMESPACE_BEGIN=namespace apl {"
        "APL_NAMESPACE_END=}"
)