cmake_minimum_required (VERSION 3.10)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (bliss)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_FORMAT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_LIMIT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/bliss")

add_subdirectory(lib/Basic)
add_subdirectory(lib/Lexer)

add_executable(bliss bliss.cpp)

add_dependencies(bliss
    Basic
    Lexer
    )

target_link_libraries(bliss
    Basic
    Lexer
    )
