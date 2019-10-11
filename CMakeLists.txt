cmake_minimum_required (VERSION 3.10)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (bliss)

set(CMAKE_CXX_FLAGS "-g -O0 -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_FORMAT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_LIMIT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/include/bliss")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/lib/llvm-8/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/lib/llvm-8/lib -lLLVM-8")

add_subdirectory(lib/Basic)
add_subdirectory(lib/FrontEnd)
add_subdirectory(lib/Driver)

add_executable(bliss bliss.cpp)

add_dependencies(bliss
    Driver
    Basic
    FrontEnd
    )

target_link_libraries(bliss
    Driver
    Basic
    FrontEnd
    )
