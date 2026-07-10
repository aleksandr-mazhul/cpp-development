#pragma once

#include <functional>
#include <iostream>

using AverageComparator = std::function<bool(double, double)>;

inline AverageComparator ascendingAverage()
{
    return [](double a, double b) { return a < b; };
}

inline AverageComparator descendingAverage()
{
    return [](double a, double b) { return a > b; };
}

inline AverageComparator readAverageComparatorFromKeyboard()
{
    int choice = 0;
    std::cout << "  1. По возрастанию\n  2. По убыванию\n  Ваш выбор: ";
    std::cin >> choice;
    return choice == 2 ? descendingAverage() : ascendingAverage();
}

inline const char* comparatorLabel(const AverageComparator& comp)
{
    return comp(2.0, 1.0) ? "по убыванию" : "по возрастанию";
}
