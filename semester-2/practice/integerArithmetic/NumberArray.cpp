#include "NumberArray.h"

#include <iostream>

NumberArray::NumberArray()
{
    std::cout << "Enter array size: ";
    std::cin >> size;

    array = new int[size];

    inputArray();
}

NumberArray::~NumberArray()
{
    delete[] array;
}

void NumberArray::inputArray()
{
    std::cout << "Enter elements:\n";

    int* ptr = array;

    while (ptr < array + size)
    {
        std::cin >> *ptr;
        ++ptr;
    }
}

void NumberArray::printArray() const
{
    const int* ptr = array;

    while (ptr < array + size)
    {
        std::cout << *ptr << " ";
        ++ptr;
    }

    std::cout << '\n';
}

int NumberArray::getMinDigit(int number) const
{
    int minDigit = 9;

    while (number > 0)
    {
        int digit = number % 10;

        if (digit < minDigit)
            minDigit = digit;

        number /= 10;
    }

    return minDigit;
}

int NumberArray::getMaxDigit(int number) const
{
    int maxDigit = 0;

    while (number > 0)
    {
        int digit = number % 10;

        if (digit > maxDigit)
            maxDigit = digit;

        number /= 10;
    }

    return maxDigit;
}

bool NumberArray::isSuitable(int number) const
{
    return (getMinDigit(number) + getMaxDigit(number)) % 2 == 0;
}

int NumberArray::findAnswer() const
{
    bool found = false;
    int answer = 0;

    const int* ptr = array;

    while (ptr < array + size)
    {
        if (isSuitable(*ptr))
        {
            if (!found || *ptr > answer)
            {
                answer = *ptr;
                found = true;
            }
        }

        ++ptr;
    }

    if (!found)
        return -1;

    return answer;
}

void NumberArray::run()
{
    std::cout << "\033[1;36m";
    std::cout << "\nArray:\n";
    std::cout << "\033[0m";

    printArray();

    int answer = findAnswer();

    std::cout << "\n";

    if (answer == -1)
    {
        std::cout << "\033[1;31m";
        std::cout << "Suitable numbers not found.\n";
        std::cout << "\033[0m";
    }
    else
    {
        std::cout << "\033[1;32m";
        std::cout << "Largest suitable number = ";
        std::cout << answer << '\n';
        std::cout << "\033[0m";
    }
}
