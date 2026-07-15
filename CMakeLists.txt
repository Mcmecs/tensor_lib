# 1. Standard setup and project naming
cmake_minimum_required(VERSION 3.14)
project(TensorLibrary CXX) # CXX is convention for C++

# Enforce modern C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# -03 tells the compiler to aggressively optimize loops, inline functions, and vectorize math.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")  # Capital 'O' and number 3 (-O3)

# Tell CMake where to look for your header (.h) file
include_directories(include)

# 2. Build the main program
# This links main.cpp together into an executable called "tensor_app"
add_executable(tensor_app src/main.cpp)

# Benchmarking executable
add_executable(tensor_benchmark src/benchmark.cpp)

# 3. Fetch and Configure GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Make GoogleTest available to our project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. Build the Test Suite
enable_testing()

# Create a separate executable specifically for running tests
add_executable(tensor_tests tests/test_matrix.cpp)

# Link the GoogleTest framework to our test executable
target_link_libraries(tensor_tests GTest::gtest_main)

#Tell CMake to discover and register our tests
include(GoogleTest)
gtest_discover_tests(tensor_tests)