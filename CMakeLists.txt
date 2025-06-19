cmake_minimum_required(VERSION 3.20)
project(${CONAN_PROJECT_NAME} VERSION ${CONAN_PROJECT_VERSION} LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp")

add_library(alarm-point-lib ${src} ${hdr})
target_include_directories(alarm-point-lib PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/apl/
)
target_include_directories(alarm-point-lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)

target_link_libraries(alarm-point-lib PUBLIC
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator
)

target_compile_definitions(alarm-point-lib PUBLIC
        "APL_NAMESPACE_BEGIN=namespace apl {"
        "APL_NAMESPACE_END=}"
)

add_subdirectory(test)

# rbd implementation
file(GLOB src "${CMAKE_SOURCE_DIR}/implementations/rbd/src/*.cpp")
file(GLOB hdr "${CMAKE_SOURCE_DIR}/implementations/rbd/include/*.hpp")

add_executable(rbd-impl ${src} ${hdr})
add_executable(alarm-point-lib::rbd-impl ALIAS rbd-impl)
target_include_directories(rbd-impl PRIVATE
        ${CMAKE_SOURCE_DIR}/implementations/rbd/include
)
target_link_libraries(rbd-impl PRIVATE
        alarm-point-lib
        rbd
)

# Convert schema file to a C++ header
file(READ "${CMAKE_SOURCE_DIR}/schemas/config.schema.json" SCHEMA_CONTENTS)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/schema.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/generated/schema.hpp
)
target_include_directories(alarm-point-lib PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/generated
)