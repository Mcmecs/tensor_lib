#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef> 
#include <iostream> 
#include <stdexcept> // Needed to throw errors

template <typename T>
class Matrix {
private:
    size_t rows_;        // Number of rows
    size_t cols_;       // Number of columns
    T* data_;       // Pointer to our flat, raw 1D array of floats
    /*
    size_t: unsigned integer and size scales to hardware CPU
        - rows and cols for a matrix can get large e.g., high-resolution 3D tensor easily exceed 2 billion elements
        - 1D memory mapping (i x TotalColumns + j)
    */

public:
    
    Matrix(size_t rows, size_t cols); // Constructor: Allocates memory for a rows x cols matrix initialized to 0.0f
    ~Matrix(); // Destructor: Frees the dynamically allocated memory to avoid leaks

    // Copy Constructor and Copy Assignment Operator (Rule of Three)
    Matrix(const Matrix& other); // Copy constructor: Used when creating a new matrix from an existing one (e.g., Matrix B = A;)
    Matrix& operator=(const Matrix& other); // Copy Assignment Operator: Used when assigning to an already existing matrix (e.g., B = A;)

    // Move Constructor and Move Assignment Operator (Rule of Five)
    // The 'noexcept' keword tells the compiler this function will never throw an error, which allows the C++ Standard Library to optimize it even further.
    Matrix(Matrix&& other) noexcept : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
        // Critical step: We stole the pointer (data_ = other.data_), if we don't nullify the original object, its Destructor will run and delete[]
        // the memory we just stole, causing our program to crash
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) { // Protect against A = std::move(A)
            // 1. Free out existing memory
            delete[] data_;

            // 2. Steal the data from 'other'
            rows_ = other.rows_;
            cols_ = other.cols_;
            data_ = other.data_;

            // 3. Nullify the source object so it doesn't delete our stolen memory
            other.rows_ = 0;
            other.cols_ = 0;
            other.data_ = nullptr;
        }

        return *this;
    }

    // Getter methods for dimensions
    size_t getRows() const;
    size_t getCols() const;

    // Operator Overload
    T& operator()(size_t row, size_t col); // Set () operator: mat(0, 0) = 1.0f;
    T operator()(size_t row, size_t col) const; // Get () operator: float weight = math(1, 0);
    Matrix operator+(const Matrix& other) const; // Operator Overloading the '+' symbol for Matrix addition
    Matrix operator-(const Matrix& other) const; // Opeartor overloading the '-' symbol for Matrix substraction
    Matrix operator+(T scalar) const; // Scalar addition
    Matrix operator*(T scalar) const; // Scalar multiplication
    Matrix operator*(const Matrix& other) const; // Overloading '*' for Matrix to Matrix multiplication

    // Helper functions
    Matrix transpose() const; //Matrix transposition
    Matrix hadamard(const Matrix& other) const; // Element-wise multiplication (multiple A(1,1) by B(1,1)): its called Hadamard product

    void print() const;
};

// 1. Constructor: Allocating Memory on the Heap
template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    // We calculate the total number of elements needed
    size_t total_elements = rows_ * cols_;

    // new[] asks the OS for a contiguous block of memory on the heap.
    // The () at the end automatically initializes all elements to 0.0f
    data_ = new T[total_elements]();
}

// 2. Destructor: Preventing Memory Leak
template <typename T>
Matrix<T>::~Matrix() {
    // Since we used new[] to allocate an array, we must use delete[] to free it.
    delete[] data_;
}

// Deep Copy Constructor
template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    size_t total_elements = rows_ * cols_;
    data_ = new T[total_elements];

    // Copy the values from other, not just the pointer address
    for (size_t i = 0; i < total_elements; ++i) {
        data_[i] = other.data_[i];
    }
}

// Deep Copy Assignment
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
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
template <typename T>
size_t Matrix<T>::getRows() const { return rows_; } // return the size of rows

template <typename T>
size_t Matrix<T>::getCols() const { return cols_; } // return the size of columns

// 4. Operator Overloading (read/write)
// This allows us to write: my_matrix(1, 2) = 5.5f;
template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col) {
    // Here is out 2D to 1D mapping forumula
    return data_[row * cols_ + col];
}

// 5. Opereator Overloading (Read-Only)
// This is used when the matrix is marked as 'const' and cannot be modified.
template <typename T>
T Matrix<T>::operator()(size_t row, size_t col) const {
    return data_[row * cols_ + col]; // mapping forumla from 2D tensor to 1D array
}

// Operator Overloading operator+
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
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

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    if (cols_ != other.cols_ || rows_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions much match for matrix substraction.");
    }

    Matrix result(rows_, cols_);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }

    return result;
}

// Scalar Addition and Multiplication
template <typename T>
Matrix<T> Matrix<T>::operator+(T scalar) const {
    size_t total_elements = rows_ * cols_; 
    Matrix result(rows_, cols_);
    
    // Single loop since adding the same number to each element
    for (size_t i = 0; i < total_elements; ++i) {
        result.data_[i] = this->data_[i] + scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    size_t total_elements = rows_ * cols_;
    Matrix result(rows_, cols_);

    for (size_t i = 0; i < total_elements; ++i) {
        result.data_[i] = this->data_[i] * scalar;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
    // Check the columns match rows of other (inner dimensions)
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions are incompatible for multiplication.");
    }

    Matrix result(rows_, other.cols_); // Create matrix based on outer dimensions

    // Optimized: Swapped the j and k loops for Cache Locality.
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t k = 0; k < cols_; ++k) {
            for (size_t j = 0; j < other.cols_; ++j) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }

    return result;
}

// Helper Functions
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix result(cols_, rows_);

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::hadamard(const Matrix& other) const {
    if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
        throw std::invalid_argument("Matrix dimensions are incompatible for Hadamard product.");
    }

    Matrix result(rows_, cols_);
    size_t total_elements = cols_ * rows_;

    for (size_t i = 0; i < total_elements; ++i) {
        result.data_[i] = this->data_[i] * other.data_[i];
    }

    return result;
}

template <typename T>
void Matrix<T>::print() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            // Using our overloaded () operator to read the value
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
}

#endif