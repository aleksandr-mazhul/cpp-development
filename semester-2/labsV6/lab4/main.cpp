#include "jagged_matrix.h"
#include <iostream>

void runAllTests();

int main()
{
    int** matrix;
    int* rowSize;
    int rowCount = 4;

    allocateJaggedMatrix(matrix, rowSize, rowCount);

    std::cout << "Before:\n";
    printJaggedMatrix(matrix, rowSize, rowCount);

    sortRows(matrix, rowSize, rowCount);

    std::cout << "\nAfter:\n";
    printJaggedMatrix(matrix, rowSize, rowCount);

    freeMatrix(matrix, rowSize, rowCount);

    std::cout << "\nRunning tests...\n";
    runAllTests();

    return 0;
}
