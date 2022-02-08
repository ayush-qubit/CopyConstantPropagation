set(LLVM_LINK_COMPONENTS core support irreader passes transformutils)
add_executable(Driver Driver.cpp)
set_target_properties(Driver PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti"
)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/vasco)

llvm_config (Driver ${LLVM_LINK_COMPONENTS})

target_link_libraries(Driver PRIVATE CopyConstantAnalysis)