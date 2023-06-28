cmake_minimum_required(VERSION 3.13)

set (module_name async)
set (utility_name test_async)
project(${module_name})

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(${module_name} VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE async_headers include/async/*.h)
file(GLOB_RECURSE async_sources src/async/*.cpp)

file(GLOB_RECURSE bin_headers include/utility/*.h)
file(GLOB_RECURSE bin_sources src/utility/*.cpp)

#add_library(${module_name} SHARED ${async_sources} ${async_headers})
add_library(${module_name} ${async_sources} ${async_headers})
add_executable(${utility_name} ${bin_sources} ${bin_headers})

message("compiler=" ${CMAKE_CXX_COMPILER} " version=" ${CMAKE_CXX_COMPILER_VERSION})

target_include_directories(${module_name}
    PUBLIC "include"
)

target_link_libraries(${utility_name} PRIVATE
    ${module_name}
)

# project install
install(TARGETS ${utility_name} RUNTIME DESTINATION bin)

install(TARGETS ${module_name}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_NAME "${module_name}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# Tests
#add_subdirectory(test)
