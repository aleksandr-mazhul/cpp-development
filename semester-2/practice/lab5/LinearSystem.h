#pragma once

#ifndef LAB5_SOURCE_DIR
#define LAB5_SOURCE_DIR "/Users/alexandermazhul/projects/archive/cpp-development/semester-2/practice/lab5"
#endif

constexpr int MAX_N = 20;
constexpr double EPS = 1e-9;

constexpr const char* DEFAULT_MATRIX_FILE = "matrix.bin";
constexpr const char* DEFAULT_VECTOR_FILE = "vector.bin";
constexpr const char* DEFAULT_RESULT_FILE = "result.txt";

bool readSize(const char* path, int& n);
bool readMatrixRow(const char* path, int n, int rowIndex, double* row);
bool writeMatrixRow(const char* path, int n, int rowIndex, const double* row);
bool readMatrixElement(const char* path, int n, int rowIndex, int colIndex, double& value);
bool swapMatrixRows(const char* path, int n, int rowA, int rowB);

bool readVectorTerm(const char* path, int n, int index, double& value);
bool writeVectorTerm(const char* path, int n, int index, double value);
bool swapVectorTerms(const char* path, int n, int indexA, int indexB);

bool writeMatrixBinary(const char* path, int n, const double* matrixRowMajor);
bool writeVectorBinary(const char* path, int n, const double* vector);

void createBinaryFiles(const char* matrixPath = DEFAULT_MATRIX_FILE,
                       const char* vectorPath = DEFAULT_VECTOR_FILE);
void viewBinaryFiles(const char* matrixPath = DEFAULT_MATRIX_FILE,
                     const char* vectorPath = DEFAULT_VECTOR_FILE);

bool solveSystemGauss(const char* matrixPath, const char* vectorPath, const char* resultPath,
                      double* solutionOut = nullptr, bool quiet = false);
void viewResultFile(const char* path = DEFAULT_RESULT_FILE);

void printSystemTable(int n, const double* matrixRowMajor, const double* vector);
void printSystemEquations(int n, const double* matrixRowMajor, const double* vector);
void printSolution(int n, const double* solution);
