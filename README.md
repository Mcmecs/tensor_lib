# TensorLib: High-Performance C++ Matrix Library #
A lightweight, high-performance Matrix math library built from scratch in C++ and exported to Python.

This project demonstrates core systems engineering principles, including manual memory management, cache-locality optimization, SIMD vectorization, and C++/Python interoperability.

## Features ##
* __Memory Safe:__ Implemented the Rule of Five (Move Semantics) for zero-copy memory transfers and strict heap management.
* __Cache Optimized:__ Matrix multiplication loops are structured (i, k, j) to maximize CPU L1 cache hits.
* __SIMD Vectorized:__ Compiled with `-O3` flags to enable Single Instruction, Multiple Data hardware accceleration.
* __Python Bindings:__ Seamlessly exposed to Python via Pybind11.

## Build Instruction (Linux/WSL) ##

### Prerequisites ###
* CMake (3.14+)
* G++ (Supporting C++17)
* Python 3 & python3-dev

### Compilation ###
Clone the repository and build using CMake:
```
mkdir build
cd build
cmake ..
make
```

## Running the C++ Test Suite ##
The library uses GoogleTest for continuous integration. To verify the math and memory safety locally:
```
cd build
./tensor_tests
```

## Python Integration ##
Once compiled, the library generates a `.so` shared object that can be imported directly into Python.
```
import sys
sys.path.append('./build')
import tensor_ext

# Create matrices
A = tensor_ext.Matrix(2, 2)
A.set(0, 0, 1.0)
A.set(1, 1, 1.0)

B = tensor_ext.Matrix(2, 2)
B.set(0, 0, 5.0)

# Execute SIMD-accelerated C++ math from Python
C = A * B
C.print()
```
