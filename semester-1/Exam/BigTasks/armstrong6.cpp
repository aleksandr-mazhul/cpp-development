#include <iostream>
using namespace std;


int pows(int x, int y);

int countOfDigits(int number);

int sumOfDigitsInPow(int number);

bool isArmstrong(int number);

int sumOfEvenArmstrong(int* array, int a, int b, int n);

int main()
{
    int array[]{


        2, 4,
        5, 7, 8, 10, 19, 7, 20, 65, 324, 2, 53, 54, 6, 57, 68, 67, 89, 35, 2, 4, 7, 6, 12, 31, 31
    };
    int n = sizeof(array) / sizeof(int);
    int a = 3;
    int b = 488;
    cout << sumOfEvenArmstrong(array, a, b, n);
}


int pows(int x, int y)
{
    int result{1};
    for (int i{0}; i < y; i++)
    {
        result *= x;
    }
    return result;
}

int countOfDigits(int number)
{
    int i{0};
    for (; number != 0; i++)
    {
        number /= 10;
    }
    return i;
}


int sumOfDigitsInPow(int number)
{
    int x = countOfDigits(number);
    int sum{0};
    for (int i{0}; i < x; i++)
    {
        int digit = number % 10;
        number = (number - digit) / 10;
        sum += pows(digit, x);
    }
    return sum;
}

bool isArmstrong(int number)
{
    if (number < 10)
    {
        return true;
    }
    if (number == sumOfDigitsInPow(number))
    {
        return true;
    }
    return false;
}


int sumOfEvenArmstrong(int* array, int a, int b, int n)
{
    int sum{0};
    int counter{1};
    for (int* p{array}; p < array + n; p++)
    {
        if (isArmstrong(*p) && *p > a && *p < b && counter % 2 == 0)
        {
            sum += *p;
        }
        counter++;
    }
    return sum;
}
