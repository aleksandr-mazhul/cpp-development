#include "array_utils.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <ctime>
using namespace std;


void swap(double& a, double& b) noexcept
{
    double temp = a;
    a = b;
    b = temp;
}

void initArray(double* a, int n, double minValue, double maxValue)
{
    srand(time(nullptr));
    for (size_t i = 0; i < n; i++)
    {
        double random = rand() / static_cast<double>(RAND_MAX);
        a[i] = minValue + random * (maxValue - minValue);
    }
}

void printArray(const double* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}


// part1
int findLastNegativeNumWithEvenPos(const double* a, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        if (i % 2 == 0 && a[i] < 0)
        {
            return i;
        }
    }
    return -1;
}

void reverse(double* a, size_t n, size_t start, size_t end)
{
    if (start >= n || end >= n || start > end)
    {
        return;
    }
    size_t steps = (end - start + 1) / 2;
    for (size_t j = 0; j < steps; j++)
    {
        swap(a[start + j], a[end - j]);
    }
}

//part1*


// part2
void cyclicLeftShift(double* a, size_t n, size_t k, size_t start, size_t end)
{
    size_t partSize = end - start + 1;
    k = k % partSize;
    if (k == 0) return;

    reverse(a, n, start, start + k - 1);
    reverse(a, n, start + k, end);
    reverse(a, n, start, end);
}

void cyclicTranspositionToTheLeftOfThirdOfThird(double* a, size_t k, int n)
{
    int thirdSize = n / 3;
    int start = 2 * thirdSize;
    int end = n - 1;
    int partSize = end - start + 1;
    k = k % partSize;
    if (k == 0) return;
    cyclicLeftShift(a, n, k, start, end);
}

// part2*

// part3
void selectionSort(double* a, size_t n, size_t start, size_t end)
{
    for (size_t i{start}; i < end; i++)
    {
        size_t minIndex = i;
        for (size_t j{i + 1}; j <= end; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(a[i], a[minIndex]);
        }
    }
}

inline void sortBySelectingElementsWithOddIndex(double* a, int n)
{
    for (size_t i{1}; i < n; i += 2)
    {
        size_t minIndex = i;
        for (size_t j{i + 2}; j < n; j += 2)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(a[i], a[minIndex]);
        }
    }
}

// part3*
