#pragma once
#include <cstddef>
double** allocateMatrix(size_t rows, size_t cols);

void freeMatrix(double** matrix, size_t rows);

void printMatrix(double** matrix, size_t rows, size_t cols);

double calcElementLib(size_t i, size_t j);

double calcElementTaylor(size_t i, size_t j);

void buildMatrixLib(double** matrix, size_t rows, size_t cols);
void buildMatrixTaylor(double** matrix, size_t rows, size_t cols);

double cosTaylor(double x);


bool almostEqual(double a, double b, double eps = 1e-6);

void testCalcElementLib();
void testCalcElementTaylor();
void testDifferentIndices();
void testLibVsTaylor();
void testMatrixBuild();

void runAllTests();