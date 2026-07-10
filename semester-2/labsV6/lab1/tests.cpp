#include <cmath>
#include <iostream>
#include <string>
#include "array_utils.h"
using namespace std;

bool equals(double a, double b, double eps = 1e-6)
{
    return fabs(a - b) < eps;
}

void printTestResult(const string& testName, bool result)
{
    cout << "[TEST] " << testName << ": "
        << (result ? "PASS" : "FAIL") << endl;
}

bool testInitArrayRange()
{
    double a[5];
    initArray(a, 5, -1.0, 1.0);

    for (int i = 0; i < 5; ++i)
    {
        if (a[i] < -1.0 || a[i] > 1.0) return false;
    }
    return true;
}

bool testReverseFullArray()
{
    double a[] = {1, 2, 3, 4, 5};
    double expected[] = {5, 4, 3, 2, 1};

    reverse(a, 5, 0, 4);

    for (int i = 0; i < 5; ++i)
    {
        if (!equals(a[i], expected[i])) return false;
    }
    return true;
}

bool testCyclicLeftShift()
{
    double a[] = {1, 2, 3, 4};
    double expected[] = {2, 3, 4, 1};

    cyclicLeftShift(a, 4, 1, 0, 3);

    for (int i = 0; i < 4; ++i)
    {
        if (!equals(a[i], expected[i])) return false;
    }
    return true;
}


bool testSelectionSort()
{
    double a[] = {3.5, -1.2, 7.0, 0.0};
    double expected[] = {-1.2, 0.0, 3.5, 7.0};

    selectionSort(a, 4, 0, 3);

    for (int i = 0; i < 4; ++i)
    {
        if (!equals(a[i], expected[i])) return false;
    }
    return true;
}
