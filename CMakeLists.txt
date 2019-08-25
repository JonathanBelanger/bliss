cmake_minimum_required (VERSION 3.10)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project (bliss)

include_directories(BEFORE SYSTEM
    /home/belanger/projects/llvm-project/llvm/include
    /home/belanger/projects/llvm-project/build/include
    /home/belanger/projects/llvm-project/build/lib/clang/10.0.0/include
    )

set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_FORMAT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_LIMIT_MACROS")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${bliss_SOURCE_DIR}/include/bliss")

add_subdirectory(lib/Lexer)
add_subdirectory(lib/AST)

add_executable(bliss lib/bliss.cpp)

add_dependencies(bliss
    Lexer
    AST
    )

target_link_libraries(bliss
    -L/home/belanger/projects/llvm-project/build/lib 
    LLVMX86Disassembler
    LLVMX86AsmParser
    LLVMX86CodeGen
    LLVMGlobalISel
    LLVMSelectionDAG
    LLVMAsmPrinter
    LLVMDebugInfoDWARF
    LLVMCodeGen
    LLVMScalarOpts
    LLVMInstCombine
    LLVMAggressiveInstCombine
    LLVMTransformUtils
    LLVMBitWriter
    LLVMX86Desc
    LLVMMCDisassembler
    LLVMX86Utils
    LLVMX86Info
    LLVMMCJIT
    LLVMExecutionEngine
    LLVMTarget
    LLVMAnalysis
    LLVMProfileData
    LLVMRuntimeDyld
    LLVMObject
    LLVMMCParser
    LLVMBitReader
    LLVMBitstreamReader
    LLVMMC
    LLVMDebugInfoCodeView
    LLVMDebugInfoMSF
    LLVMCore
    LLVMRemarks
    LLVMBinaryFormat
    LLVMSupport
    LLVMDemangle
    -lz -lrt -ldl -ltinfo -lpthread -lm
    )

        
