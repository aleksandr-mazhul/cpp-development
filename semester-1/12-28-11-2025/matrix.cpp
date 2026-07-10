#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

constexpr size_t Size = 10;

void initMatrix(int Matrix[][Size], size_t size);

void printMatrix(int Matrix[][Size], size_t size);

void transposeMatrix(int Matrix[][Size], size_t size);

void snakeDisplay(int Matrix[][Size], size_t size, int* array);

void swap(int& a, int& b);

void swap(int* a, int* b);

int main()
{
    int matrix[Size][Size]{};
    int array[Size * Size]{};
    // int n{};
    // cout << "Enter matrix size: " << n << endl;
    // cin >> n;
    // initMatrix(matrix, Size);
    // printMatrix(matrix, Size);

    for (int i = 2; i < Size + 1; i++)
    {
        initMatrix(matrix, i);
        cout << " matrix" << endl;
        printMatrix(matrix, i);
        cout << endl;

        transposeMatrix(matrix, i);
        cout << " transpose matrix" << endl;
        printMatrix(matrix, i);

        snakeDisplay(matrix, i, array);
        for (int* p{array}; p < array + i * i; p++)
        {
            cout << *p << " ";
        }
        cout << endl;
    }

    int x{1}, y{2};
    swap(x, y);
    swap(&x, &y);


    return 0;
}

void initMatrix(int Matrix[][Size], size_t size)
{
    for (size_t i = 0, k = 1; i < size; i++)
    {
        for (size_t j = 0; j < size; j++, k++)
        {
            Matrix[i][j] = k; // n*i + j +1 вместо k
        }
    }
}


void printMatrix(int Matrix[][Size], size_t size)
{
    for (size_t i = 0, k = 1; i < size; i++)
    {
        for (size_t j = 0; j < size; j++, k++)
        {
            cout << setw(6) << Matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void transposeMatrix(int Matrix[][Size], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            swap(&Matrix[i][j], &Matrix[j][i]);
        }
    }
}


void swap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


void snakeDisplay(int Matrix[][Size], size_t size, int* array)
{
    for (size_t i = 0, k = 0; i < size; i++)
    {
        if (i % 2 == 1)
        {
            for (int j = size - 1; j >= 0; j--, k++)
            {
                array[k] = Matrix[i][j];
            }
        }
        else
        {
            for (int j = 0; j < size; j++, k++)
            {
                array[k] = Matrix[i][j];
            }
        }
    }
}
