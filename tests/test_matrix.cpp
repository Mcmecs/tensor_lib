#include <gtest/gtest.h>
#include "matrix.h"

// TEST is a GoogleTest macro.
// "MatrixTest" is the category (test_suite_name). 
// "Initialization"  is the specific test name (test_name).
TEST(MatrixTest, Initialization) {
    // 1. Setup: Create a 2x3 matrix
    Matrix mat(2, 3);

    // 2. Validate Dimensions using EXPECT_EQ (Expect Equal) - use getting functions
    EXPECT_EQ(mat.getRows(), 2);
    EXPECT_EQ(mat.getCols(), 3);

    // 3. Validate Memory Allocation
    // We want to prove that the 'new[]()' command successfully
    // initialized every single slot in our flat 1D array to 0.0f.
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_FLOAT_EQ(mat(i, j), 0.0f);
        }
    }
}

TEST(MatrixTest, Addition) {
    // Declare 2 x 2 matrices A & B
    Matrix A(2, 2);
    Matrix B(2, 2);

    // Initialize Matrix A
    A(0, 0) = 1.0f;
    A(0, 1) = 2.0f;
    A(1, 0) = 3.0f;
    A(1, 1) = 4.0f;

    // Inititalize Matrix B
    B(0, 0) = 1.0f;
    B(0, 1) = 2.0f;
    B(1, 0) = 3.0f;
    B(1, 1) = 4.0f;

    // Perform addition C = A + B
    Matrix C = A + B;

    // Validate results of C
    EXPECT_FLOAT_EQ(C(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(C(0, 1), 4.0f);
    EXPECT_FLOAT_EQ(C(1, 0), 6.0f);
    EXPECT_FLOAT_EQ(C(1, 1), 8.0f);

}