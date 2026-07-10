#pragma once

#include <array>
#include <functional>
#include <iostream>

const size_t Size = 10;

using IntegerArray = std::array<int, Size>;
using PredicatePointer = bool (*)(int);
using Predicate = std::function<bool(int)>;

// базовые фильтры
void filterOnlyPositive(const IntegerArray& numbers);
void filterOnlyNegative(const IntegerArray& numbers);
void filterOnlyEven(const IntegerArray& numbers);
void filterOnlyOdd(const IntegerArray& numbers);

// универсальные
void filterByPredicate(const IntegerArray& numbers, PredicatePointer predicate);
void filterByPredicate(const IntegerArray& numbers, Predicate predicate);