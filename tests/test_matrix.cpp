#include <gtest/gtest.h>
#include "matrix.h"

// 1. Degine the Test Fixture Class
class MatrixTest : public ::testing::Test {
protected:
    // Variables accessible to all TEST_F blocks.
    Matrix<float>* A; // Pointer is used because there's no default constructor with zero arguments
    Matrix<float>* B;

    // SetUp() runs immediately before every single TEST_F block.
    void SetUp() override {
        A = new Matrix<float>(2, 2);
        B = new Matrix<float>(2, 2);

        (*A)(0, 0) = 1.0f; (*A)(0, 1) = 2.0f;
        (*A)(1, 0) = 3.0f; (*A)(1, 1) = 4.0f;

        (*B)(0, 0) = 2.0f; (*B)(0, 1) = 4.0f;
        (*B)(1, 0) = 6.0f; (*B)(1, 1) = 8.0f;

    }

    // TearDown() runs immediately after every single TEST_F. 
    void TearDown() override {
        // Clean up pointers to prevent memory leaks
        delete A;
        delete B;
    }
};

// TEST is a GoogleTest macro.
// "MatrixBasicTest" is the category (test_suite_name). 
// "Initialization"  is the specific test name (test_name).
TEST(MatrixBasicTest, Initialization) {
    // 1. Setup: Create a 2x3 matrix
    Matrix<float> mat(2, 3);

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

TEST_F(MatrixTest, Addition) {
    Matrix C = (*A) + (*B);

    // Validate results of C
    EXPECT_FLOAT_EQ(C(0, 0), 3.0f);
    EXPECT_FLOAT_EQ(C(0, 1), 6.0f);
    EXPECT_FLOAT_EQ(C(1, 0), 9.0f);
    EXPECT_FLOAT_EQ(C(1, 1), 12.0f);

}

TEST_F(MatrixTest, Substraction) {
    Matrix C = (*B) - (*A); 

    EXPECT_FLOAT_EQ(C(0,0), 1.0f);
    EXPECT_FLOAT_EQ(C(0,1), 2.0f);
    EXPECT_FLOAT_EQ(C(1,0), 3.0f);
    EXPECT_FLOAT_EQ(C(1,1), 4.0f);
}

TEST_F(MatrixTest, ScalarAddition) {
    Matrix C = (*A) + 1.0f;

    EXPECT_FLOAT_EQ(C(0,0), 2.0f);
    EXPECT_FLOAT_EQ(C(0,1), 3.0f);
    EXPECT_FLOAT_EQ(C(1,0), 4.0f);
    EXPECT_FLOAT_EQ(C(1,1), 5.0f);
}

TEST_F(MatrixTest, ScalarMultiple) {
    Matrix C = (*B) * 2.0f;

    EXPECT_FLOAT_EQ(C(0,0), 4.0f);
    EXPECT_FLOAT_EQ(C(0,1), 8.0f);
    EXPECT_FLOAT_EQ(C(1,0), 12.0f);
    EXPECT_FLOAT_EQ(C(1,1), 16.0f);
}

TEST_F(MatrixTest, MatrixMultiplication) {
    Matrix<float> A(2, 3);
    A(0, 0) = 1.0f; A(0, 1) = 2.0f; A(0, 2) = 3.0f;
    A(1, 0) = 4.0f; A(1, 1) = 5.0f; A(1, 2) = 6.0f;

    Matrix<float> B(3, 2);
    B(0, 0) = 7.0f;  B(0, 1) = 8.0f;
    B(1, 0) = 9.0f;  B(1, 1) = 10.0f;
    B(2, 0) = 11.0f; B(2, 1) = 12.0f;

    Matrix<float> C = A * B;

    // Check dimensions of the new matrix
    EXPECT_EQ(C.getRows(), 2);
    EXPECT_EQ(C.getCols(), 2);

    EXPECT_FLOAT_EQ(C(0, 0), 58.0f);
    EXPECT_FLOAT_EQ(C(0, 1), 64.0f);
    EXPECT_FLOAT_EQ(C(1, 0), 139.0f);
    EXPECT_FLOAT_EQ(C(1, 1), 154.0f);
}

TEST_F(MatrixTest, MatrixTranspose) {
    Matrix<float> A(2, 3);
    A(0, 0) = 1.0f; A(0, 1) = 2.0f; A(0, 2) = 3.0f;
    A(1, 0) = 4.0f; A(1, 1) = 5.0f; A(1, 2) = 6.0f;

    Matrix<float> B = A.transpose();

    EXPECT_EQ(B.getRows(), 3);
    EXPECT_EQ(B.getCols(), 2);


    EXPECT_FLOAT_EQ(B(0,0), 1.0f);
    EXPECT_FLOAT_EQ(B(0,1), 4.0f);
    EXPECT_FLOAT_EQ(B(1,0), 2.0f);
    EXPECT_FLOAT_EQ(B(1,1), 5.0f);
    EXPECT_FLOAT_EQ(B(2,0), 3.0f);
    EXPECT_FLOAT_EQ(B(2,1), 6.0f);
}

TEST_F(MatrixTest, MatrixHadamard) {
    Matrix C = (*A).hadamard(*B);

    EXPECT_FLOAT_EQ(C(0, 0), 2.0f);
    EXPECT_FLOAT_EQ(C(0, 1), 8.0f);
    EXPECT_FLOAT_EQ(C(1, 0), 18.0f);
    EXPECT_FLOAT_EQ(C(1, 1), 32.0f);

}

TEST(MatrixTemplateTest, IntegerMatrix) {
    Matrix<int> intMat(2, 2);

    intMat(0, 0) = 1; intMat(0, 1) = 2;
    intMat(1, 0) = 3; intMat(1, 1) = 4;

    Matrix<int> result = intMat * 2;

    EXPECT_EQ(result(0, 0), 2);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 6);
    EXPECT_EQ(result(1, 1), 8);
}