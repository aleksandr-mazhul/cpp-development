#include <iostream>
#include <iomanip>
using namespace std;

void initMatrix(int matrix[][100], size_t y, size_t x);

void printMatrix(int matrix[][100], size_t y, size_t x);

void swap(int& a, int& b);

void swapFirstForth(int matrix[][100], size_t y, size_t x);

void swapSecondThird(int matrix[][100], size_t y, size_t x);

void swapDiagonals(int matrix[][100], size_t y, size_t x);

int main()
{
    int matrix[100][100]{};
    swapDiagonals(matrix, 6, 6);
}


void swap(int& a, int& b)
{
    int c = a;
    a = b;
    b = c;
}

void initMatrix(int matrix[][100], size_t y, size_t x)
{
    int k = 1;
    for (size_t i = 0; i < y; i++)
    {
        for (size_t j = 0; j < x; j++)
        {
            matrix[i][j] = k++;
        }
    }
}

void printMatrix(int matrix[][100], size_t y, size_t x)
{
    for (size_t i = 0; i < y; i++)
    {
        for (size_t j = 0; j < x; j++)
        {
            cout << setw(6) << matrix[i][j];
        }
        cout << endl;
    }
}

void swapFirstForth(int matrix[][100], size_t y, size_t x)
{
    int SizeY = y / 2;
    int SizeX = x / 2;
    for (size_t i = 0; i < SizeY; i++)
    {
        for (size_t j = 0; j < SizeX; j++)
        {
            swap(matrix[i][j], matrix[i + SizeY][j + SizeX]);
        }
    }
}


void swapSecondThird(int matrix[][100], size_t y, size_t x)
{
    size_t halfY = y /
        2;
    size_t halfX = x / 2;


    for (size_t i = 0; i < halfY; i++)
    {
        for (size_t j = halfX; j < x; j++)
        {
            swap(matrix[i][j], matrix[i + halfY][j - halfX]);
        }
    }
}

void swapDiagonals(int matrix[][100], size_t y, size_t x)
{
    initMatrix(matrix, 6, 6);
    swapFirstForth(matrix, 6, 6);
    swapSecondThird(matrix, 6, 6);
    printMatrix(matrix, 6, 6);
}
