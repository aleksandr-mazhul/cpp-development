#include "tests.h"

#include "algorithms.h"

#include <array>
#include <iostream>

using namespace std;

void printTestResult(const string& testName, bool result)
{
    cout << "[TEST] " << testName << ": " << (result ? "PASS" : "FAIL") << endl;
}

bool testTransform()
{
    array < int, 3 > a = {1, 2, 3};

    transformArray(a, [](int x) { return x * 2; });

    return a[0] == 2 && a[1] == 4 && a[2] == 6;
}

bool testCountIf()
{
    array < int, 5 > a = {-1, 2, 3, -5, 6};

    return countIf(a, [](int x) { return x > 0; }) == 3;
}

bool testSort()
{
    array < int, 3 > a = {3, 1, 2};

    sortArray(a, [](int a, int b) { return a < b; });

    return a[0] == 1 && a[1] == 2 && a[2] == 3;
}

void runTests()
{
    printTestResult("transform", testTransform());
    printTestResult("countIf", testCountIf());
    printTestResult("sort", testSort());
}
