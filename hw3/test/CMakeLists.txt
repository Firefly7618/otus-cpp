cmake_minimum_required(VERSION 3.10)

# Unit Tests
add_executable(test_allocator ${PROJECT_SOURCE_DIR}/test/test_allocator.cpp)

# Gtest headers
target_include_directories(test_allocator
    PRIVATE "${PROJECT_SOURCE_DIR}/../googletest/googletest/include"
    PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Gtest library link
target_link_libraries(test_allocator gtest gtest_main)


add_test(test_allocator test_allocator)

