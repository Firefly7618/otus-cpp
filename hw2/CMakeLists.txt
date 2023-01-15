cmake_minimum_required(VERSION 3.10)

set (module_name ip_filter)
project(${module_name})

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(${module_name} VERSION ${PROJECT_VERSION})

file(GLOB_RECURSE headers include/*.h)
file(GLOB_RECURSE sources src/*.cpp)

add_executable(${module_name} ${sources} ${headers})

set_target_properties(${module_name} PROPERTIES
   CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

message("compiler=" ${CMAKE_CXX_COMPILER} " version=" ${CMAKE_CXX_COMPILER_VERSION})

target_include_directories(${module_name}
    PUBLIC "include"
 )

 if (MSVC)
      target_compile_options(ip_filter PRIVATE
        /W4
       )
 else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror -fconcepts
    )
endif()

# project install
install(TARGETS ${module_name} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_NAME "${module_name}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
