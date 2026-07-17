# Changelog

All notable changes to this project will be summarized in this file.

## [1.0.0] - 2026-07-17
### Added
* Python bindings via Pybind11 to expose Matrix class and math operations. 
* Comprehensive `README.md` with build instructions.
* Core matrix arithmetic operations (Hadamard product, transpose, scalar addition/multiplication, and operator overloads).
* GitHub Actions CI pipeline (`ci.yml`) for automated testing.
* Standardized CMake build system (`CMakeLists.txt`)
* The `Matrix` class header file with manual heap allocation (`new[]`)

### Changes
* Refactored `Matrix` class into a generic template.
* Implemented Move Semantics (Rule of Five) for sero-copy memory transfers.
* Optimized matrix multiplication loops for cache locality (`i, k, j`).
Enabled `-O3` compiler flags for SIMD vectorization.

### Fixed
* Resolved memory leaks during matrix destruction.