#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>

template <typename T>
using Comparer = std::function<bool(T, T)>;

template <typename TIn, typename TOut>
using Converter = std::function<TOut(TOut, TIn)>;

template <typename T>
using Array = std::array<T, 10>;

int keyAbs(int x);
int keyDigitCount(int x);
int keySumOfDigits(int x);
int keyLastDigit(int x);
int keyModulo(int x, int n);

template <typename T, std::size_t left, std::size_t right>
void display(const T* arr)
{
    for (std::size_t i = left; i <= right; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

template <typename T, typename U, typename FunctionKey>
void bubbleSort(T* arr, int left, int right, const FunctionKey& key)
{
    const int n = right - left + 1;
    U* keys = new U[n];

    for (int i = 0; i < n; ++i)
    {
        keys[i] = key(arr[i + left]);
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = n - 1; j > i; --j)
        {
            if (keys[j] < keys[j - 1])
            {
                std::swap(keys[j], keys[j - 1]);
                std::swap(arr[j + left], arr[j - 1 + left]);
            }
        }
    }

    delete[] keys;
}

template <typename T>
void bubbleSort(T* arr, int left, int right, const Comparer<T>& comparer)
{
    for (int i = left; i < right; ++i)
    {
        for (int j = right; j > i; --j)
        {
            if (comparer(arr[j], arr[j - 1]))
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

template <typename TIn, typename TOut>
Array<TOut> convert(const Array<TIn>& source, const Converter<TIn, TOut>& converter)
{
    Array<TOut> result{};

    for (std::size_t i = 0; i < source.size(); ++i)
    {
        result[i] = converter(result[i], source[i]);
    }

    return result;
}

void bubbleSortByValueAsc(int* arr, int left, int right);
void bubbleSortByValueDesc(int* arr, int left, int right);
void bubbleSortByAbs(int* arr, int left, int right);
void bubbleSortByDigitCount(int* arr, int left, int right);
void bubbleSortBySumOfDigits(int* arr, int left, int right);
void bubbleSortByLastDigit(int* arr, int left, int right);

