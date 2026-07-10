#include "filters.h"

void filterOnlyPositive(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] > 0)
            std::cout << numbers[i] << " ";
    }
}

void filterOnlyNegative(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < 0)
            std::cout << numbers[i] << " ";
    }
}

void filterOnlyEven(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (!(numbers[i] % 2))
            std::cout << numbers[i] << " ";
    }
}

void filterOnlyOdd(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] % 2)
            std::cout << numbers[i] << " ";
    }
}

void filterByPredicate(const IntegerArray& numbers, PredicatePointer predicate)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (predicate(numbers[i]))
            std::cout << numbers[i] << " ";
    }
}

void filterByPredicate(const IntegerArray& numbers, Predicate predicate)
{
    for (auto number : numbers)
    {
        if (predicate(number))
            std::cout << number << " ";
    }
}

