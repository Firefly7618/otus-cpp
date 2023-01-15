cmake_minimum_required(VERSION 3.7)

project(otus-cpp)

if (DEFINED SUBPROJECT)
    if (SUBPROJECT STREQUAL "HW1")
        add_subdirectory(hw1)
    elseif(SUBPROJECT STREQUAL "HW2")
        add_subdirectory(hw2)
    else()
        message("unknown project")
    endif()
endif()
