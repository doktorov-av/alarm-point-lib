cmake_minimum_required(VERSION 3.16)
project(${CONAN_PROJECT_NAME} VERSION ${CONAN_PROJECT_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp")

add_library(alarm-point-lib ${src} ${hdr})
target_include_directories(alarm-point-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(alarm-point-lib PUBLIC
        "APL_NAMESPACE_BEGIN=namespace apl {"
        "APL_NAMESPACE_END=}"
)

add_subdirectory(test)