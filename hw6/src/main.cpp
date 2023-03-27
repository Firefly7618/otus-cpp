#include "Matrix.h"

int main()
{
    Matrix<int, 0> matrix;

    // fill the matrix
    for (int i=0, j=9; i < 10; ++i, --j)
    {
        matrix.set(i,i,i);
        matrix.set(i,j,j);
    }

    // print the values
    for (std::size_t row =1; row < 9; ++row)
    {
        for (std::size_t column = 1; column < 9; ++column)
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