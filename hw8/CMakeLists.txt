cmake_minimum_required(VERSION 3.13)

set (module_name bayan)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(${module_name} VERSION ${PROJECT_VERSION})

find_package(Boost COMPONENTS program_options filesystem regex REQUIRED)

file(GLOB_RECURSE headers include/*.h)
file(GLOB_RECURSE sources src/*.cpp)

add_executable(${module_name} ${sources} ${headers})

message("compiler=" ${CMAKE_CXX_COMPILER} " version=" ${CMAKE_CXX_COMPILER_VERSION})

target_include_directories(${module_name}
    PUBLIC "include"
    PRIVATE ${Boost_INCLUDE_DIR}
)

set_target_properties(${module_name} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(${module_name}
    ${Boost_LIBRARIES}
)

# project install
install(TARGETS ${module_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_NAME "${module_name}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# Tests
#add_subdirectory(test)
