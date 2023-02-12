cmake_minimum_required(VERSION 3.10)

set (test_name test_print_ip)

# Unit Tests
add_executable(${test_name} ${PROJECT_SOURCE_DIR}/test/test_print_ip.cpp)

# Gtest headers
target_include_directories(${test_name}
    PRIVATE "${PROJECT_SOURCE_DIR}/../googletest/googletest/include"
    PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Gtest library link
target_link_libraries(${test_name} gtest gtest_main)


add_test(${test_name} ${test_name})
