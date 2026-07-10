#include <iostream>
using namespace std;

// прототип функции: принимает два указателя
void printArray(int* begin, int* end);

int main()
{
    int array[]{1, 21, 13, 64, 5};

    cout << "Initialized array: ";
    printArray(begin(array), end(array)); // <- вот тут магия
    return 0;
}

void printArray(int* begin, int* end)
{
    for (int* p = begin; p < end; p++)
    {
        cout << *p << " ";
    }
}
