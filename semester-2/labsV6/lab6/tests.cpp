#include "tests.h"
#include "process.h"
#include <iostream>

bool arraysEqual(const int* a, int sizeA, const int* b, int sizeB)
{
    if (sizeA != sizeB) return false;
    for (int i = 0; i < sizeA; ++i)
        if (a[i] != b[i]) return false;
    return true;
}

void testEvenSquare()
{
    int data[] = {-3, 2, 5, 4, -6, 7};
    int expected[] = {4, 16, 36};

    int outSize = 0;
    int* out = process(data, 6,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 3);
    if (ok)
        std::cout << "testEvenSquare PASSED\n";
    else
        std::cout << "testEvenSquare FAILED\n";

    delete[] out;
}

void testEmptyArray()
{
    int data[] = {1, 2, 3};
    int outSize = 0;
    int* out = process(data, 0,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = (outSize == 0 && out == nullptr);
    if (ok)
        std::cout << "testEmptyArray PASSED\n";
    else
        std::cout << "testEmptyArray FAILED\n";

    delete[] out; // delete[] nullptr безопасно
}

void testNoMatchingElements()
{
    int data[] = {1, 3, 5, 7};
    int outSize = 0;
    int* out = process(data, 4,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = (outSize == 0);
    if (ok)
        std::cout << "testNoMatchingElements PASSED\n";
    else
        std::cout << "testNoMatchingElements FAILED\n";

    delete[] out;
}

void testAllMatch()
{
    int data[] = {2, 4, 6};
    int expected[] = {4, 16, 36};

    int outSize = 0;
    int* out = process(data, 3,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 3);
    if (ok)
        std::cout << "testAllMatch PASSED\n";
    else
        std::cout << "testAllMatch FAILED\n";

    delete[] out;
}

void testNegativeValues()
{
    int data[] = {-4, -2, -8};
    int expected[] = {16, 4, 64};

    int outSize = 0;
    int* out = process(data, 3,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 3);
    if (ok)
        std::cout << "testNegativeValues PASSED\n";
    else
        std::cout << "testNegativeValues FAILED\n";

    delete[] out;
}

void testSingleMatchingElement()
{
    int data[] = {7, 4, 9};
    int outSize = 0;
    int* out = process(data, 3,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = (outSize == 1 && out[0] == 16);
    if (ok)
        std::cout << "testSingleMatchingElement PASSED\n";
    else
        std::cout << "testSingleMatchingElement FAILED\n";

    delete[] out;
}

void testOddAbs()
{
    int data[] = {-5, 2, -3, 8};
    int expected[] = {5, 3};

    int outSize = 0;
    int* out = process(data, 4,
                       [](int x) { return x % 2 != 0; },
                       [](int x) { return x < 0 ? -x : x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 2);
    if (ok)
        std::cout << "testOddAbs PASSED\n";
    else
        std::cout << "testOddAbs FAILED\n";

    delete[] out;
}

void testNamedLambdas()
{
    auto filterEven = [](int x) { return x % 2 == 0; };
    auto transformSquare = [](int x) { return x * x; };

    int data[] = {1, 2, 3, 4};
    int expected[] = {4, 16};

    int outSize = 0;
    int* out = process(data, 4, filterEven, transformSquare, outSize);

    bool ok = arraysEqual(out, outSize, expected, 2);
    if (ok)
        std::cout << "testNamedLambdas PASSED\n";
    else
        std::cout << "testNamedLambdas FAILED\n";

    delete[] out;
}

void testLargeArray()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int expected[] = {4, 16, 36, 64, 100, 144, 196, 256, 324, 400};

    int outSize = 0;
    int* out = process(data, 20,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 10);
    if (ok)
        std::cout << "testLargeArray PASSED\n";
    else
        std::cout << "testLargeArray FAILED\n";

    delete[] out;
}

void testLargeArrayAllMatch()
{
    int data[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
    int expected[] = {4, 16, 36, 64, 100, 144, 196, 256, 324, 400, 484, 576, 676, 784, 900};

    int outSize = 0;
    int* out = process(data, 15,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = arraysEqual(out, outSize, expected, 15);
    if (ok)
        std::cout << "testLargeArrayAllMatch PASSED\n";
    else
        std::cout << "testLargeArrayAllMatch FAILED\n";

    delete[] out;
}

void testLargeArrayNoMatch()
{
    int data[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

    int outSize = 0;
    int* out = process(data, 10,
                       [](int x) { return x % 2 == 0; },
                       [](int x) { return x * x; },
                       outSize);

    bool ok = (outSize == 0);
    if (ok)
        std::cout << "testLargeArrayNoMatch PASSED\n";
    else
        std::cout << "testLargeArrayNoMatch FAILED\n";

    delete[] out;
}
