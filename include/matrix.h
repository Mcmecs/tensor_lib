#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef> 

class Matrix {
private:
    size_t rows_;        // Number of rows
    size_t cols_;       // Number of columns
    float* data_;       // Pointer to our flat, raw 1D array of floats
    /*
    size_t: unsigned integer and size scales to hardware CPU
        - rows and cols for a matrix can get large e.g., high-resolution 3D tensor easily exceed 2 billion elements
        - 1D memory mapping (i x TotalColumns + j)
    */

public:
    // Constructor: Allocates memory for a rows x cols matrix initialized to 0.0f
    Matrix(size_t rows, size_t cols);       

    // Destructor: Frees the dynamically allocated memory to avoid leaks
    ~Matrix(); 

    // Copy constructor: Used when creating a new matrix from an existing one (e.g., Matrix B = A;)
    Matrix(const Matrix& other);
    // Copy Assignment Operator: Used when assigning to an already existing matrix (e.g., B = A;)
    Matrix& operator=(const Matrix& other);

    // Getter methods for dimensions
    size_t getRows() const;
    size_t getCols() const;

    float& operator()(size_t row, size_t col);
    float operator()(size_t row, size_t col) const;

    // Operator Overloading the '+' symbol for Matrix addition
    Matrix operator+(const Matrix& other) const;

    void print() const;
};

#endif