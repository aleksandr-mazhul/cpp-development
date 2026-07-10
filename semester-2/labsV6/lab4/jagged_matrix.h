#pragma once


void allocateJaggedMatrix(int**& matrix, int*& rowSize, int rowCount);
void printJaggedMatrix(int** matrix, const int* rowSize, int rowCount);
void sortRows(int** matrix, int* rowSize, int rowCount);
void freeMatrix(int** matrix, const int* rowSize, int rowCount);

int criterionPositive(const int* row, int length);
