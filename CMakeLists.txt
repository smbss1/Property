cmake_minimum_required(VERSION 3.20)
project(Property)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(cmake/CPM.cmake)
CPMAddPackage(
    NAME fox_signal
    GITHUB_REPOSITORY smbss1/Signal
    GIT_TAG main
)

add_library(fox_property STATIC include/Property.hpp)
target_include_directories(fox_property PUBLIC "include")
target_link_libraries(fox_property PUBLIC fox_signal)

set(PROPERTY_TEST 1)

if (PROPERTY_TEST)
    add_subdirectory(tests)
endif()
