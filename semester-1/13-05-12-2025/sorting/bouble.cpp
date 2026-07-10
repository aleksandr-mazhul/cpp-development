#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int& A, int& B);

void initArray(int array[], size_t Size);

void printArray(int array[], size_t Size);

void bubbleSort(int array[], size_t Size);

void selectionSort(int array[], size_t Size);

void insertionSort(int array[], size_t Size);


int constexpr N{100};


int main()
{
    srand(time(nullptr));
    int array[N]{};
    int n{10};
    initArray(array, n);
    printArray(array, n);

    bubbleSort(array, n);
    cout << "bubble";
    printArray(array, n);

    selectionSort(array, n);
    cout << "selection";
    printArray(array, n);

    insertionSort(array, n);
    cout << "insertion";
    printArray(array, n);
}

void swap(int& A, int& B)
{
    int C = A;
    A = B;
    B = C;
}

void initArray(int array[], size_t Size)
{
    for (size_t i{0}; i < Size; i++)
    {
        array[i] = rand() % 30 + 0;
    }
}

void printArray(int array[], size_t Size)
{
    cout << "Array: ";
    for (size_t i{0}; i < Size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}


void bubbleSort(int array[], size_t Size)
{
    bool swapped = false;

    if (Size < 2) return;
    do
    {
        swapped = false;
        for (size_t i{0}; i < Size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        --Size;
    }
    while (swapped == true);
}


void selectionSort(int array[], size_t Size)
{
    for (size_t i{0}; i < Size - 1; i++)
    {
        size_t minIndex{i};
        for (size_t j{i + 1}; j < Size; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }
        swap(array[i], array[minIndex]);
    }
}


void insertionSort(int array[], size_t Size)
{
    for (size_t i{1}; i < Size; i++)
    {
        int key = array[i];

        size_t j = i;
        while (j > 0 && array[j - 1] > key)
        {
            array[j] = array[j - 1];
            --j;
        }
        array[j] = key;
    }
}
