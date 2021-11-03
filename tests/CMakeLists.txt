cmake_minimum_required(VERSION 3.20)

enable_testing()

file(GLOB_RECURSE TESTS_SRCS "*.cpp")

add_executable(tests ${TESTS_SRCS})
target_link_libraries(tests ${CONAN_LIBS})
target_include_directories(tests PRIVATE "../include")

add_test(tests tests)
