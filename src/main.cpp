#include <iostream>
#include "matrix.h"

int main() {
    std::cout << "Allocating a 3x3 matrix on the heap" << std::endl;

    // 1. Create a 3x3 matrix
    // This automatically calls the Constructor and uses new[] to grab memory
    Matrix<float> mat(3, 3);

    // 2. Modify values using the overloaded () operator
    mat(0, 0) = 1.5f;
    mat(1, 1) = 2.5f;
    mat(2, 2) = 3.5f;

    std::cout << "\nCurrent Matrix contents:" << std::endl;

    // 2. Display the grid
    mat.print();

    std::cout << "\nExiting program. Destructor will now free the memory." << std::endl;

    // 4. As soon as 'retun 0' hits and 'mat' goes out of scope, your destructor is 
    // automatically called, running delete[] to prevent a leak.
    
    return 0;
}