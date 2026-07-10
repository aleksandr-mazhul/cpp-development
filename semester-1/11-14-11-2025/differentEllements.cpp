#include <iostream>

int countOfUniqueElements(int* pointer, int size);
void initArray(int* pointer, int size);
void displayArray(int* pointer, int size);
bool isUniqueElements(int* pointer, int size, int value);

int main()
{
    const int n = 15;
    int array[n]{0};
    int k{};

    std::cout << "Enter k: ";
    std::cin >> k;

    initArray(array, n);
    std::cout << "Source array: ";
    displayArray(array, n);
    std::cout << std::endl;

    int uniqueCount = countOfUniqueElements(array, n);
    std::cout << "Count of unique elements: " << uniqueCount << std::endl;

    return 0;
}

void displayArray(int* pointer, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << pointer[i] << " ";
    }
}

int countOfUniqueElements(int* pointer, int size)
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (isUniqueElements(pointer, i, pointer[i]))
        {
            ++count;
        }
    }
    return count;
}

void initArray(int* pointer, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "a[" << (i + 1) << "]: ";
        std::cin >> pointer[i];
    }
}

bool isUniqueElements(int* pointer, int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (pointer[i] == value)
        {
            return false;
        }
    }
    return true;
}
