#include "logic.h"

#include <cmath>

bool filter(int value)
{
    return std::abs(value) < 10;
}

int transform(int value)
{
    return std::abs(value);
}

int* process(
    const int* src,
    int size,
    bool (*filterFunc)(int),
    int (*transformFunc)(int),
    int& outSize)
{
    int count = 0;

    for (int i = 0; i < size; ++i)
    {
        if (filterFunc(src[i]))
            ++count;
    }

    outSize = count;

    if (count == 0)
        return nullptr;

    int* result = new int[count];

    int j = 0;
    for (int i = 0; i < size; ++i)
    {
        if (filterFunc(src[i]))
        {
            result[j++] = transformFunc(src[i]);
        }
    }

    return result;
}