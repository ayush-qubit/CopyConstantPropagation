cmake_minimum_required(VERSION 3.16)
project(CopyConstantPropagation)
set(LLVM_ROOT "/usr/lib/llvm-12" CACHE PATH "/usr/lib/llvm-12")

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS} include)
link_directories(${LLVM_LIBRARY_DIRS})

include_directories("/usr/local/include/vasco")
include_directories("/usr/local/include/spatial")
include_directories("./vasco")

add_library(Vasco SHARED IMPORTED)
set_target_properties(Vasco PROPERTIES IMPORTED_LOCATION "/usr/local/lib/libDriver.so")

add_subdirectory(lib)
add_subdirectory(src)