#ifndef MATRIX_UTILS_H_
#define MATRIX_UTILS_H_

#define UNUSED(variable) (void)variable

#include <iostream>

namespace mtrx
{
template <class T>
void print_array_2d(T &array2d, size_t limit1, size_t limit2)
{
    for (size_t i = limit1; i < limit2 + 1; ++i)
    {
        for (size_t j = limit1; j < limit2 + 1; ++j)
        {
            try
            {
                auto val = array2d[i][j];
                std::cout << val;
            }
            catch (const std::exception &e)
            {
                throw;
            }

            if (j == limit2)
                std::cout << std::endl;
            else
                std::cout << " ";
        }
    }
}

} // namespace mtrx

#endif /* MATRIX_UTILS_H_ */
