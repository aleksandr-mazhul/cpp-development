#include <iostream>
using namespace std;

void initArrayFibanachi(int* array, int b, int n);

int sumOfFibanachi(int* array, int a, int b);

int main()
{
    int n{100};
    int array[n];
    initArrayFibanachi(array, 500, 100);
    cout << sumOfFibanachi(array, 4, 500);
}

void initArrayFibanachi(int* array, int b, int n)
{
    array[0] = 0;
    array[1] = 1;
    for (int* p{array + 2}; p < array + n; p++)
    {
        *p = *(p - 1) + *(p - 2);
        if (*p >= b)
        {
            break;
        }
    }
}

int sumOfFibanachi(int* array, int a, int b)
{
    int sum{0};
    for (int* p{array}; p < array + 100 && *p < b; p++)
    {
        if (*p > a)
        {
            sum += *p;
        }
    }
    return sum;
}
