cmake_minimum_required(VERSION 3.20)
project(Property)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(PROPERTY_TEST 1)

if (PROPERTY_TEST)
    add_subdirectory(tests)
endif()
