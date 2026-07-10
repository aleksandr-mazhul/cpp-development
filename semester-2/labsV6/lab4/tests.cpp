#include <iostream>
#include "jagged_matrix.h"

bool equals(int a, int b)
{
    return a == b;
}


void testSortByPositive()
{
    int rows = 3;


    int* lengths = new int[rows]{3, 1, 2};
    int** matrix = new int*[rows];

    matrix[0] = new int[3]{1, -2, 3};
    matrix[1] = new int[1]{-5};
    matrix[2] = new int[2]{7, 8};

    sortRows(matrix, lengths, rows);

    int first = criterionPositive(matrix[0], lengths[0]);
    int second = criterionPositive(matrix[1], lengths[1]);
    int third = criterionPositive(matrix[2], lengths[2]);

    bool ok = (first >= second && second >= third);

    if (ok)
        std::cout << "[TEST] testSortByPositive: PASS\n";
    else
        std::cout << "[TEST] testSortByPositive: FAIL\n";

    freeMatrix(matrix, lengths, rows);
}


void testSingleRow()
{
    int rows = 1;

    int* lengths = new int[1]{4};
    int** matrix = new int*[1];
    matrix[0] = new int[4]{1, 2, 3, 4};

    sortRows(matrix, lengths, rows);

    bool ok = (lengths[0] == 4);

    if (ok)
        std::cout << "[TEST] testSingleRow: PASS\n";
    else
        std::cout << "[TEST] testSingleRow: FAIL\n";

    freeMatrix(matrix, lengths, rows);
}


void testRowsWithZeros()
{
    int rows = 2;

    int* lengths = new int[rows]{0, 2};
    int** matrix = new int*[rows];

    matrix[0] = new int[0];
    matrix[1] = new int[2]{10, -10};

    sortRows(matrix, lengths, rows);

    int first = criterionPositive(matrix[0], lengths[0]);

    bool ok = (first == 1);

    if (ok)
        std::cout << "[TEST] testRowsWithZeros: PASS\n";
    else
        std::cout << "[TEST] testRowsWithZeros: FAIL\n";

    freeMatrix(matrix, lengths, rows);
}


void testMixedValues()
{
    int rows = 3;

    int* lengths = new int[rows]{2, 3, 1};
    int** matrix = new int*[rows];

    matrix[0] = new int[2]{-1, -2};
    matrix[1] = new int[3]{1, 2, 3};
    matrix[2] = new int[1]{5};

    sortRows(matrix, lengths, rows);

    int first = criterionPositive(matrix[0], lengths[0]);
    int last = criterionPositive(matrix[2], lengths[2]);

    bool ok = (first >= last);

    if (ok)
        std::cout << "[TEST] testMixedValues: PASS\n";
    else
        std::cout << "[TEST] testMixedValues: FAIL\n";

    freeMatrix(matrix, lengths, rows);
}


void runAllTests()
{
    testSortByPositive();
    testSingleRow();
    testRowsWithZeros();
    testMixedValues();
}