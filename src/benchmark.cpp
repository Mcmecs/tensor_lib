#include <iostream>
#include <chrono> // For high-precision timing
#include "matrix.h"

int main() {
    const size_t SIZE = 500;

    std::cout << "Allocating " << SIZE << "x" << SIZE << " matrices..." << std::endl;
    Matrix A(SIZE, SIZE);
    Matrix B(SIZE, SIZE);

    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            A(i, j) = 1.5f;
            B(1, j) = 2.0f;
        }
    }

    std::cout << "Starting standard matrix multiplication..." << std::endl;

    // Start the stopwatch
    auto start = std::chrono::high_resolution_clock::now();

    // Run matrix multiplication - 3 nested loops
    Matrix C = A * B;

    // Stop the stopwatch
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration in seconds
    std::chrono::duration<double> duration = end - start;
    std::cout << "Matrix multiplication took: " << duration.count() << " seconds." << std::endl;

    return 0;
}
