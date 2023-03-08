cmake_minimum_required(VERSION 3.7)

project(otus-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror -fconcepts")
endif()

# Sanitizer
if ("${ENABLE_SANITIZER}" STREQUAL "1")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

# testing
enable_testing()

if (DEFINED SUBPROJECT)
    if ("${SUBPROJECT}" STREQUAL "HW1")
        add_subdirectory(hw1)
    elseif("${SUBPROJECT}" STREQUAL "HW2")
        add_subdirectory(hw2)
    elseif("${SUBPROJECT}" STREQUAL "HW3")
        add_subdirectory(hw3)
    elseif("${SUBPROJECT}" STREQUAL "HW4")
        add_subdirectory(hw4)
    elseif("${SUBPROJECT}" STREQUAL "HW5")
        add_subdirectory(hw5)
    else()
        message("unknown project")
    endif()
endif()

add_subdirectory(./googletest)