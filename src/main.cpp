#include "matrix.h"
#include <cassert>
#include <exception>
#include <iostream>

int main(int argc, char const *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    try
    {
        mtrx::Matrix<int, 0> matrix;
        for (int i = 0; i < 10; ++i)
        {
            matrix[i][i] = i;
            matrix[i][9 - i] = 9 - i;
        }

        mtrx::print_array_2d(matrix, 1, 8);
        std::cout << matrix.size() << std::endl;

        for(auto c: matrix)
        {
        auto [ key, v] = c;
        auto [ x, y ] = key;
        std::cout << "[" << x << "] " << "[" << y << "] " << v << std::endl;
        }

        ((matrix[100][100] = 314) = 0) = 217;
        std::cout << "Check ((matrix[100][100] = 314) = 0) = 217 returns => " << matrix[100][100] << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "matrix version " << mtrx::version() << std::endl;
    }

    return 0;
}
