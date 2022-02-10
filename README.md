# CopyConstantPropogation

Implementation of CopyConstant Propagation at interprocedural level using VASCO framework.

# Build instructions

Run the following command in the project directory. Before running following command VASCO must be installed.

```bash
mkdir build
cd build
cmake .. && make
```

# Run instruction
```bash
cd testcases
./run.sh ./inputs/test1.c
```
An output txt file in the folder testcases/outputs/test1.ll.txt is created contains output of the analysis
