#### About

This software has been released as a part of an SERB project on precise and scalable program analysis. The project started late, funding was delayed signigicantly so this is not a complete work and is a snapshot of the work when the sponsored project ended. Subsequently work is being carried out separately.


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
