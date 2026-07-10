#include "sorting_utils.h"


int keyAbs(int x)
{
    return std::abs(x);
}

int keyDigitCount(int x)
{
    if (x == 0)
    {
        return 1;
    }

    int count = 0;
    int t = std::abs(x);
    while (t)
    {
        t /= 10;
        ++count;
    }
    return count;
}

int keySumOfDigits(int x)
{
    int t = std::abs(x);
    int sum = 0;
    while (t)
    {
        sum += t % 10;
        t /= 10;
    }
    return sum;
}

int keyLastDigit(int x)
{
    return std::abs(x % 10);
}

int keyModulo(int x, int n)
{
    return ((x % n) + n) % n;
}

static void bubbleSortByOrder(int* arr, int left, int right, bool ascending)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (ascending)
            {
                if (arr[j] < arr[j - 1])
                {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
            else
            {
                if (arr[j] > arr[j - 1])
                {
                    std::swap(arr[j], arr[j - 1]);
                }
            }
        }
    }
}

void bubbleSortByValueAsc(int* arr, int left, int right)
{
    bubbleSortByOrder(arr, left, right, true);
}

void bubbleSortByValueDesc(int* arr, int left, int right)
{
    bubbleSortByOrder(arr, left, right, false);
}

void bubbleSortByAbs(int* arr, int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (std::abs(arr[j]) < std::abs(arr[j - 1]))
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void bubbleSortByDigitCount(int* arr, int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (keyDigitCount(arr[j]) < keyDigitCount(arr[j - 1]))
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void bubbleSortBySumOfDigits(int* arr, int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (keySumOfDigits(arr[j]) < keySumOfDigits(arr[j - 1]))
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void bubbleSortByLastDigit(int* arr, int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (keyLastDigit(arr[j]) < keyLastDigit(arr[j - 1]))
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

