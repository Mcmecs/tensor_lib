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
    
    Matrix(size_t rows, size_t cols); // Constructor: Allocates memory for a rows x cols matrix initialized to 0.0f
    ~Matrix(); // Destructor: Frees the dynamically allocated memory to avoid leaks

    Matrix(const Matrix& other); // Copy constructor: Used when creating a new matrix from an existing one (e.g., Matrix B = A;)
    Matrix& operator=(const Matrix& other); // Copy Assignment Operator: Used when assigning to an already existing matrix (e.g., B = A;)

    // Getter methods for dimensions
    size_t getRows() const;
    size_t getCols() const;

    // Operator Overload
    float& operator()(size_t row, size_t col); // Set () operator: mat(0, 0) = 1.0f;
    float operator()(size_t row, size_t col) const; // Get () operator: float weight = math(1, 0);
    Matrix operator+(const Matrix& other) const; // Operator Overloading the '+' symbol for Matrix addition
    Matrix operator-(const Matrix& other) const; // Opeartor overloading the '-' symbol for Matrix substraction

    Matrix operator+(float scalar) const; // Scalar addition
    Matrix operator*(float scalar) const; // Scalar multiplication

    void print() const;
};

#endif