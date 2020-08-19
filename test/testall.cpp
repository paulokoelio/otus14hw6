#include "matrix.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(version_fn, full_test)
{
    const char *first = PROJECT_VERSION;
    const char *second = mtrx::version();

    std::string ver(second);

    EXPECT_STREQ(first, second);
    EXPECT_STRCASEEQ(first, second);
    EXPECT_GE(ver.length(), 5);
}

TEST(matrix_cl, full_test)
{

    mtrx::Matrix<long, -1> matrix;
    EXPECT_EQ(matrix.size(), 0) << " NOTE: method .size() returned incorrect data.";
    
    auto a = matrix[0][0];
    EXPECT_EQ(a == -1, true)<< " NOTE: operator== of class Matrix::MValue returned incorrect data or problem in copy constructor.";

    mtrx::Matrix<float> m2;
    EXPECT_EQ(m2.value(10000, 10000), 0)<< " NOTE: creation of Matrix with default value=0 is not working or problem in method .value(i,j).";

    matrix[100][100] = 314;
    EXPECT_EQ(matrix[100][100] == 314, true) << " NOTE: problem in assignmet operator= of class Matrix::MValue.";
    EXPECT_EQ(matrix.size() , 1) << " NOTE: problem in method .size() after assignmet operator= of class Matrix::MValue.";
    
    std::string res;
    for (auto c : matrix)
    {
        auto [key, v] = c;
        auto [x, y] = key;
        res = std::to_string(x) + std::to_string(y) + std::to_string(v);
    }
    EXPECT_STREQ( "100100314" , res.c_str()) << " NOTE: problem in .begin() or .end() method or in iteration through internal std::map member @values .";
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}