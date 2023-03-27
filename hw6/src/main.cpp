#include "Matrix.h"

int main()
{
    Matrix<int, 0> matrix;
    int const matrix_size = 10;

    // fill the matrix
    for (int i = 0, j = matrix_size - 1; i < matrix_size; ++i, --j)
    {
        matrix.set(i,i,i);
        matrix.set(i,j,j);
    }

    int const matrix_fragment_size = 8;

    // print the values
    for (std::size_t row = 1; row <= matrix_fragment_size; ++row)
    {
        for (std::size_t column = 1; column <= matrix_fragment_size; ++column)
        {
            std::cout << matrix[row][column];
            if (column != 8)
            {
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << "Number of filled cells = " << matrix.size() << std:: endl;

    // print the cells with non-default values
    for (auto const& [row_num, row] : matrix)
    {
        for (auto const& [col_num, value] : row)
        {
            std::cout << "(" << row_num << "," << col_num << ") = " << value << std::endl;
        }
    }

    return 0;
}