#include <iostream>
#include "Array.cpp"

int main()
{
    Array array;
    for (int i = 1; i <= 7; i++)
    {
        array.add(i);
    }

    cout << array << endl;
}
