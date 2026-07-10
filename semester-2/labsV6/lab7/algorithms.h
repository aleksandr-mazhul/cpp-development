#pragma once
#include <array>
#include <iostream>
#include <random>
#include <type_traits>

template <typename T, size_t N>
void initArray(std::array<T, N>& a, T minValue, T maxValue)
{
    std::mt19937 gen(std::random_device{}());

    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> dist(minValue, maxValue);
        for (size_t i{0}; i < N; ++i)
        {
            a[i] = dist(gen);
        }
    }
    else
    {
        std::uniform_real_distribution<T> dist(minValue, maxValue);
        for (size_t i{0}; i < N; ++i)
        {
            a[i] = dist(gen);
        }
    }
}

template <typename T, size_t N>
void printArray(const std::array<T, N>& a)
{
    for (size_t i{0}; i < N; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T, size_t N, typename Func>
void transformArray(std::array<T, N>& a, Func func)
{
    for (size_t i{0}; i < N; ++i)
    {
        a[i] = func(a[i]);
    }
}

template <typename T, size_t N, typename Predicate>
int countIf(const std::array<T, N>& a, Predicate predicate)
{
    int count{0};
    for (size_t i{0}; i < N; ++i)
    {
        if (predicate(a[i]))
        {
            ++count;
        }
    }
    return count;
}

template <typename T, size_t N, typename Predicate>
T findIf(const std::array<T, N>& a, Predicate predicate)
{
    for (size_t i{0}; i < N; ++i)
    {
        if (predicate(a[i]))
        {
            return a[i];
        }
    }
    return T{};
}

template <typename T, size_t N, typename Comparator>
void sortArray(std::array<T, N>& a, Comparator comp)
{
    if constexpr (N < 2)
    {
        return;
    }

    for (size_t i{0}; i < N - 1; ++i)
    {
        for (size_t j{0}; j < N - i - 1; ++j)
        {
            if (!comp(a[j], a[j + 1]))
            {
                std::swap(a[j], a[j + 1]);
            }
        }
    }
}

struct Square
{
    template <typename T>
    T operator()(T x) const
    {
        return x * x;
    }
};
