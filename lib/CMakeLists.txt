add_library(CopyConstantAnalysis SHARED
    CopyConstant.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

set_target_properties(CopyConstantAnalysis PROPERTIES
    COMPILE_FLAGS "-g -std=c++14 -fno-rtti"
)
