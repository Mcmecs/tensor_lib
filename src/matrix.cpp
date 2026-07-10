#include "matrix.h"
#include <iostream> 
#include <stdexcept> // Needed to throw errors

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

// Deep Copy Constructor
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    size_t total_elements = rows_ * cols_;
    data_ = new float[total_elements];

    // Copy the values from other, not just the pointer address
    for (size_t i = 0; i < total_elements; ++i) {
        data_[i] = other.data_[i];
    }
}

// Deep Copy Assignment
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this; // protect against self assignment

    delete[] data_;

    rows_ = other.rows_;
    cols_ = other.cols_;

    size_t total_elements = rows_ * cols_;
    data_ = new float[total_elements];

    for (size_t i = 0; i < total_elements; ++i) {
        data_[i] = other.data_[i]; 
    }
    
    return *this;
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

// Operator Overloading operator+
Matrix Matrix::operator+(const Matrix& other) const {
    // I think there should be some exception if the dimension doesn't match
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrix dimensions must match for matrix addition.");
    }

    // Create a new matrix 
    Matrix result(rows_, cols_);
    
    // Element wise addition
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }

    return result;
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