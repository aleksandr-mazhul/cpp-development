#include "jagged_matrix.h"

#include <iostream>

void allocateJaggedMatrix(int**& matrix, int*& rowSize, int rowCount)
{
    rowSize = new int[rowCount];

    for (int i = 0; i < rowCount; i++)
    {
        rowSize[i] = i + 1;
    }

    matrix = new int*[rowCount];

    for (int i = 0; i < rowCount; i++)
    {
        matrix[i] = new int[rowSize[i]];
    }

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < rowSize[i]; j++)
        {
            matrix[i][j] = i + j;
        }
    }
}

void printJaggedMatrix(int** matrix, const int* rowSize, int rowCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < rowSize[i]; j++)
        {
            std::cout << matrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

void sortRows(int** matrix, int* rowSize, int rowCount)
{
    for (int i = 0; i < rowCount - 1; i++)
    {
        for (int j = 0; j < rowCount - i - 1; j++)
        {
            int a = criterionPositive(matrix[j], rowSize[j]);
            int b = criterionPositive(matrix[j + 1], rowSize[j + 1]);

            if (a < b)
            {
                std::swap(matrix[j], matrix[j + 1]);
                std::swap(rowSize[j], rowSize[j + 1]);
            }
        }
    }
}

int criterionPositive(const int* row, int length)
{
    int count = 0;

    for (int i = 0; i < length; i++)
    {
        if (row[i] > 0)
        {
            count++;
        }
    }

    return count;
}


void freeMatrix(int** matrix, const int* rowSize, int rowCount)
{
    for (int i = 0; i < rowCount; i++)
    {
        delete[] matrix[i];
    }

    delete[] matrix;
    delete[] rowSize;
}