#include <iostream>
using namespace std;

int sumEllements(int* array, int Size);

int fingIndex(int* array, int Size);

void testsumEllements(const char* name, int* array, int Size);

int main()
{
    // Точка равновесия в середине (индекс 14)
    int array[]{
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14,
        105,
        14, 13, 12, 11, 10,
        9, 8, 7, 6, 5, 4, 3, 2, 1
    };

    // Точка равновесия в середине (индекс 1)
    int array1[]{10, 0, 1, 1, 1, 1, 1, 5};

    // Нет точки равновесия
    int array2[]{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Точка равновесия в самом начале (индекс 0)
    int array3[]{0, 1, -1};

    // Точка равновесия в самом конце (индекс 4)
    int array4[]{1, -1, 2, -2, 0};

    // Нет точки равновесия
    int array5[]{5, 1, 9, 3, 4};


    int size = sizeof(array) / sizeof(array[0]);
    int size1 = sizeof(array1) / sizeof(array1[0]);
    int size2 = sizeof(array2) / sizeof(array2[0]);
    int size3 = sizeof(array3) / sizeof(array3[0]);
    int size4 = sizeof(array4) / sizeof(array4[0]);
    int size5 = sizeof(array5) / sizeof(array5[0]);


    testsumEllements("array", array, size);
    testsumEllements("array1", array1, size1);
    testsumEllements("array2", array2, size2);
    testsumEllements("array3", array3, size3);
    testsumEllements("array4", array4, size4);
    testsumEllements("array5", array5, size5);
}

int sumEllements(int* array, int Size)
{
    int sum{0};
    for (int i = 0; i < Size; i++)
    {
        sum += array[i];
    }
    return sum;
}

int fingIndex(int* array, int Size)
{
    int leftSum = 0;
    int rightSum = sumEllements(array, Size);

    for (int i = 0; i < Size; ++i)
    {
        rightSum -= array[i];

        if (leftSum == rightSum)
        {
            return i;
        }

        leftSum += array[i];
    }
    return -1;
}

void testsumEllements(const char* name, int* array, int Size)
{
    int idx = fingIndex(array, Size);
    cout << name << " i: ";
    if (idx == -1)
    {
        cout << "there is no such element";
    }
    else
    {
        cout << idx;
    }
    cout << endl;
}
