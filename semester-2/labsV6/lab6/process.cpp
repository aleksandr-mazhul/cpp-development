#include "process.h"

#include <functional>
#include <iostream>

using namespace std;

int* process(const int* src, int size,
             const std::function<bool(int)>& filter,
             const std::function<int(int)>& transform,
             int& outSize)
{
    if (size == 0)
    {
        outSize = 0;
        return nullptr;
    }

    int* buf = new int[size];
    int count = 0;

    for (int i = 0; i < size; ++i)
    {
        if (filter(src[i])) // lambda: filter
            buf[count++] = transform(src[i]); // lambda: transform
    }

    outSize = count;

    if (count == 0)
    {
        delete[] buf;
        return nullptr;
    }

    if (count == size)
        return buf;

    int* result = new int[count];
    for (int j = 0; j < count; ++j)
        result[j] = buf[j];
    delete[] buf;
    return result;
}

void printArr(const int* arr, int size)
{
    for (int i{0}; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
