#include "matrix.h"
#include <iostream> 

// 1. Constructor: Allocating Memory on the Heap
Matrix::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    // We calculate the total number of elements needed
    size_t total_elements = rows_ * cols_;

    // new[] asks the OS for a contiguous block of memory on the heap.
    // The () at the end automatically initializes all elements to 0.0f
    data_ = new float[total_elements]();
}

// 2. Destructor: Preventing Memory Leak
Matrix::~Matrix() {
    // Since we used new[] to allocate an array, we must use delete[] to free it.
    delete[] data_;
}

// 3. Getters
size_t Matrix::getRows() const { return rows_; } // return the size of rows
size_t Matrix::getCols() const { return cols_; } // return the size of columns

// 4. Operator Overloading (read/write)
// This allows us to write: my_matrix(1, 2) = 5.5f;
float& Matrix::operator()(size_t row, size_t col) {
    // Here is out 2D to 1D mapping forumula
    return data_[row * cols_ + col];
}

// 5. Opereator Overloading (Read-Only)
// This is used when the matrix is marked as 'const' and cannot be modified.
float Matrix::operator()(size_t row, size_t col) const {
    return data_[row * cols_ + col]; // mapping forumla from 2D tensor to 1D array
}

// 6. Helper Print Function
void Matrix::print() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            // Using our overloaded () operator to read the value
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
}