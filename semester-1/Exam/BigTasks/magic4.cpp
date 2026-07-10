#include <iostream>
using namespace std;

// int countOfDigit(int number);

int sumOfDigitsOfNumber(int number);

bool isMagicNumber(int number);

int sumOfMagicNumbers(int* array, int n, int a, int b);

int main()
{
    int array[]{2, 4, 5, 7, 8, 10, 19, 7, 20, 65, 324, 2, 53, 54, 6, 57, 68, 67, 89, 35, 2, 4, 7, 6, 12, 31, 31};
    int n = sizeof(array) / sizeof(array[0]);
    cout << sumOfMagicNumbers(array, n, 3, 40);
}


// int countOfDigit(int number) {
//     int i{1};
//     for (; number != 0; i++) {
//         number /= 10;
//     }
//     return i;
// }


int sumOfDigitsOfNumber(int number)
{
    int sum{0};
    while (number != 0)
    {
        int digit{0};
        digit = number % 10;
        sum += digit;
        number = (number - digit) / 10;
    }
    return sum;
}


bool isMagicNumber(int number)
{
    if (number <= 0)
    {
        return false;
    }
    while (number > 9)
    {
        number = sumOfDigitsOfNumber(number);
        if (number == 1)
        {
            return true;
        }
    }
    return false;
}


int sumOfMagicNumbers(int* array, int n, int a, int b)
{
    if (array == nullptr)
    {
        return 0;
    }
    int sum{0};
    for (int* p{array}; p < array + n; p++)
    {
        if (isMagicNumber(*p) && *p > a && *p < b)
        {
            sum += *p;
        }
    }
    return sum;
}
