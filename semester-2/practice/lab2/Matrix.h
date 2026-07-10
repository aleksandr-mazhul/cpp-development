#pragma once

#ifndef LAB2_SOURCE_DIR
#define LAB2_SOURCE_DIR "/Users/alexandermazhul/projects/archive/cpp-development/semester-2/practice/lab2"
#endif

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
const char* const FILE_NAME = "matrix.txt";

extern int data[MAX_ROWS][MAX_COLS];
extern int* rowPtrs[MAX_ROWS];
extern int rowCount;
extern int colCount;

bool loadMatrixFromFile();
bool loadMatrixFromPath(const char* path, bool quiet = false);
void inputMatrixFromKeyboardAndSave();
bool saveMatrixToFile();
void initRowPtrs();
void printMatrix(int highlightRow, int newRow);

int minDigit(int n);
bool isDescending(int* row, int cols);
int countEvenMinDigit(int* row, int cols);
int** findTargetRow(int& outCount);
bool insertZeroRowAfter(int** afterRow);
void insertZeroRowTask();
void runAllTests();
