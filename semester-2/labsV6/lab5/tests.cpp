#include "tests.h"
#include "logic.h"
#include <iostream>

bool arraysEqual(const int* a, int sizeA, const int* b, int sizeB)
{
    if (sizeA != sizeB) return false;

    for (int i = 0; i < sizeA; ++i)
    {
        if (a[i] != b[i]) return false;
    }

    return true;
}

void testSingleDigitAbs()
{
    int data[] = {-15, -9, -3, 0, 7, 12};
    int expected[] = {9, 3, 0, 7};

    int outSize = 0;
    int* out = process(data, 6, filter, transform, outSize);

    bool ok = arraysEqual(out, outSize, expected, 4);

    if (ok)
        std::cout << "testSingleDigitAbs PASSED\n";
    else
        std::cout << "testSingleDigitAbs FAILED\n";

    delete[] out;
}

void testNoMatch()
{
    int data[] = {10, -20, 100};

    int outSize = 0;
    int* out = process(data, 3, filter, transform, outSize);

    bool ok = (outSize == 0 && out == nullptr);

    if (ok)
        std::cout << "testNoMatch PASSED\n";
    else
        std::cout << "testNoMatch FAILED\n";

    delete[] out;
}

void testAllMatch()
{
    int data[] = {-1, 2, -3, 4};
    int expected[] = {1, 2, 3, 4};

    int outSize = 0;
    int* out = process(data, 4, filter, transform, outSize);

    bool ok = arraysEqual(out, outSize, expected, 4);

    if (ok)
        std::cout << "testAllMatch PASSED\n";
    else
        std::cout << "testAllMatch FAILED\n";

    delete[] out;
}

void runAllTests()
{
    testSingleDigitAbs();
    testNoMatch();
    testAllMatch();
}
