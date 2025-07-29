cmake_minimum_required(VERSION 3.20)

message(STATUS "APL: Configurating tests")

find_package(GTest REQUIRED)

file(GLOB src "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
file(GLOB hdr "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp")

add_executable(tests-all
        ${CMAKE_CURRENT_LIST_DIR}/src/analog_mode_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/switch_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/read_config_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/dynamic_bounds.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/static_bounds.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/tracker_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/build_points_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${hdr})
target_link_libraries(tests-all PRIVATE gtest::gtest alarm-point-lib)
target_include_directories(tests-all PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tests-all PRIVATE ${CMAKE_SOURCE_DIR}/include/apl)

add_test(
        NAME ctest_all
        COMMAND tests-all
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Testing
)
