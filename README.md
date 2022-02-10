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
./run.sh ./inputs/test<number>.c
```
An output txt file in the folder testcases/outputs/test<number>.ll.txt is created contains output of the analysis
