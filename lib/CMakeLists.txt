add_library(CopyConstantAnalysis SHARED
    DataFlowValue.cpp
    CopyConstant.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/vasco)

set_target_properties(CopyConstantAnalysis PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -O3 -fno-rtti"
)
