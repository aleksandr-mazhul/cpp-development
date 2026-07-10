#include <iostream>

void swap(int& a, int& b);
void initArray(int* pointer, int size);
void displayArray(int* pointer, int size);
// void rightShiftArray(int* pointer, int size, int k);
// void leftShiftArray(int* pointer, int size, int k);
void shift(int* pointer, int size, int k, bool right = true);
void reverseArray(int* pointer, int k, int size);
void badShiftArray(int* pointer, int size);
//void initArray(int pointer[], int size);


int main()
{
    const int n = 15;
    int array[n]{0};
    int k{};
    std::cout << "Enter k:";
    std::cin >> k;
    initArray(array, n);
    std::cout << "Source array: ";
    displayArray(array, n);
    shift(array, n, k, false);
    std::cout << std::endl;
    std::cout << "Result array: ";
    displayArray(array, n);
}

void swap(int& a, int& b)
{
    int temp{a};
    a = b;
    b = temp;
}

void initArray(int* pointer, int size)
{
    for (int i = 0; i < size; i++)
    {
        pointer[i] = i + 1; //
        //vs
        //*(pointer + i) = i + 1;
    }
}

void displayArray(int* pointer, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << pointer[i] << " ";
    }
}

void reverseArray(int* pointer, int k, int size)
{
    for (int i = 0; i < (size - k) / 2; ++i)
    {
        swap(pointer[i + k], pointer[size - i - 1]);
    }
}


void badShiftArray(int* pointer, int size, int k)
{
    // O(n*k)
    for (int i = 1; i <= k; ++i)
    {
        int temp{pointer[size - 1]};
        for (int j = size - 2; j >= 0; --j)
        {
            pointer[j + 1] = pointer[j];
        }
        pointer[0] = temp;
    }
}

// void leftShiftArray(int* pointer, int size, int k) {
//     //rightShiftArray(pointer, size, size - k);
//     reverseArray(pointer, 0, size);
//     reverseArray(pointer, 0, size - k);
//     reverseArray(pointer, size - k, size);
// }
//
// void rightShiftArray(int* pointer, int size, int k) {
//     reverseArray(pointer,0, size);//1
//     reverseArray(pointer, 0, k);//2
//     reverseArray(pointer, k, size);//3
// }

void shift(int* pointer, int size, int k, bool right)
{
    k = k % size;
    int shift = right ? k : size - k;
    reverseArray(pointer, 0, size); //1
    reverseArray(pointer, 0, shift); //2
    reverseArray(pointer, shift, size); //3
}
