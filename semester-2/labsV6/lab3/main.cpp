#include <iostream>
#include "matrix_utils.h"


int main()
{
    runAllTests();

    std::cout << "\n--- DEMO ---\n";

    size_t rows, cols;

    std::cout << "Enter rows and cols: ";
    std::cin >> rows >> cols;

    double** A = allocateMatrix(rows, cols);
    buildMatrixLib(A, rows, cols);
    std::cout << "\nMatrix (Lib):\n";
    printMatrix(A, rows, cols);

    freeMatrix(A, rows);

    double** B = allocateMatrix(rows, cols);
    buildMatrixTaylor(B, rows, cols);

    std::cout << "\nMatrix (Taylor):\n";
    printMatrix(B, rows, cols);

    freeMatrix(B, rows);

    return 0;
}
