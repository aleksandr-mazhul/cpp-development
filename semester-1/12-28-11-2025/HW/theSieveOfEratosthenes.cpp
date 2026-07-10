#include <iostream>

using namespace std;

constexpr size_t sizeMax{100};

int dimension();

void initArray(bool array[], size_t n);

void printArray(bool array[], size_t n);

void sieveArray(bool array[], size_t n);

int main()
{
    size_t n = dimension();
    bool array[sizeMax]{};
    initArray(array, n);
    sieveArray(array, n);
    printArray(array, n);
}

int dimension()
{
    while (true)
    {
        size_t n{};
        cout << "enter the number up to which you want to find the primes from the range [ 2 ; " << sizeMax << " ]:" <<
            endl;
        cin >> n;
        if (n <= sizeMax && n > 2)
        {
            return n;
        }
    }
}


void initArray(bool array[], size_t n)
{
    array[0] = false;
    array[1] = false;

    for (size_t i{2}; i < n; i++)
    {
        array[i] = true;
    }
}

void sieveArray(bool array[], size_t n)
{
    for (size_t i{2}; i * i < n; i++)
    {
        for (size_t j{i * i}; j < n; j += i)
        {
            array[j] = false;
        }
    }
}

void printArray(bool array[], size_t n)
{
    for (size_t i{0}; i < n; i++)
    {
        if (array[i] == true)
        {
            cout << i << " ";
        }
    }
}
