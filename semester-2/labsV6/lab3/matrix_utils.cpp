#include "matrix_utils.h"

#include <cmath>

#include <iostream>

double** allocateMatrix(size_t rows, size_t cols)
{
    double** matrix = new double*[rows];

    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void freeMatrix(double** matrix, size_t rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(double** matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << "    ";
        }
        std::cout << std::endl;
    }
}

double calcElementLib(size_t i, size_t j)
{
    if (i == j)
    {
        return (cos(i + j) + 2 * i - j) / ((i + j + 1) * (i + j + 1));
    }
    else
    {
        return static_cast<double>(i) - static_cast<double>(j);
    }
}

double calcElementTaylor(size_t i, size_t j)
{
    if (i == j)
    {
        return (cosTaylor(static_cast<double>(i + j)) + 2 * i - j) / ((i + j + 1) * (i + j + 1));
    }
    else
    {
        return static_cast<double>(i) - static_cast<double>(j);
    }
}

void buildMatrixLib(double** matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = calcElementLib(i, j);
        }
    }
}

void buildMatrixTaylor(double** matrix, size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            matrix[i][j] = calcElementTaylor(i, j);
        }
    }
}

double cosTaylor(double x)
{
    double term = 1.0;
    double sum = 1.0;

    for (int k = 1; k < 15; k++)
    {
        term *= -x * x / ((2 * k - 1) * (2 * k));
        sum += term;
    }

    return sum;
}


bool almostEqual(double a, double b, double eps)
{
    return std::abs(a - b) < eps;
}

void testCalcElementLib()
{
    double val = calcElementLib(1, 1);
    double expected = (cos(2) + 2 * 1 - 1) / ((1 + 1 + 1) * (1 + 1 + 1));

    if (almostEqual(val, expected))
        std::cout << "[TEST] calcElementLib (1,1): PASS\n";
    else
        std::cout << "[TEST] calcElementLib (1,1): FAIL\n";
}

void testCalcElementTaylor()
{
    double val = calcElementTaylor(1, 1);
    double expected = calcElementLib(1, 1);

    if (almostEqual(val, expected))
        std::cout << "[TEST] calcElementTaylor (1,1): PASS\n";
    else
        std::cout << "[TEST] calcElementTaylor (1,1): FAIL\n";
}

void testDifferentIndices()
{
    double val = calcElementLib(1, 2);
    double expected = 1.0 - 2.0;

    if (almostEqual(val, expected))
        std::cout << "[TEST] calcElementLib (1,2): PASS\n";
    else
        std::cout << "[TEST] calcElementLib (1,2): FAIL\n";
}

void testLibVsTaylor()
{
    bool ok = true;

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            double a = calcElementLib(i, j);
            double b = calcElementTaylor(i, j);

            if (!almostEqual(a, b))
                ok = false;
        }
    }

    if (ok)
        std::cout << "[TEST] Lib vs Taylor: PASS\n";
    else
        std::cout << "[TEST] Lib vs Taylor: FAIL\n";
}

void testMatrixBuild()
{
    size_t rows = 3, cols = 3;

    double** A = allocateMatrix(rows, cols);
    buildMatrixLib(A, rows, cols);

    bool ok = true;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (!almostEqual(A[i][j], calcElementLib(i, j)))
                ok = false;
        }
    }

    freeMatrix(A, rows);

    if (ok)
        std::cout << "[TEST] Matrix build: PASS\n";
    else
        std::cout << "[TEST] Matrix build: FAIL\n";
}

void runAllTests()
{
    testCalcElementLib();
    testCalcElementTaylor();
    testDifferentIndices();
    testLibVsTaylor();
    testMatrixBuild();
}
