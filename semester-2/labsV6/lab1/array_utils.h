#pragma once
void swap(double& a, double& b) noexcept;

void initArray(double* a, int n, double minValue, double maxValue);

void printArray(const double* a, int n);

int findLastNegativeNumWithEvenPos(const double* a, int n);

void reverse(double* a, size_t n, size_t start, size_t end);

void cyclicTranspositionToTheLeftOnK(double* a, size_t k, int n);

void cyclicTranspositionToTheLeftOfThirdOfThird(double* a, size_t k, int n);

void cyclicLeftShift(double* a, size_t n, size_t k, size_t start, size_t end);

void cyclicLeftShift(size_t n, size_t k, size_t start, size_t end);

void selectionSort(double* a, size_t n, size_t start, size_t end);


void sortBySelectingElementsWithOddIndex(double* a, int n);




