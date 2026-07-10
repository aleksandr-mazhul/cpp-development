#include <iostream>
#include <cmath>

using namespace std;

int getCountOfDigit(int number);

bool isPalindrome(int number);

int sumOfPalindromeElements(const int* array, int n, int a, int b);

int main()
{
    int array[]{11, 22, 33, 44, 121, 131, 242, 345, 456};
    cout << sumOfPalindromeElements(array, 3, 2, 20000);
}

int getCountOfDigit(int number)
{
    size_t count{0};

    if (number <= 0)
    {
        return 0;
    }

    while (number > 0)
    {
        count++;
        number /= 10;
    }
    return count;
}

// bool isPalindrome(int number) {
//     if (number <= 0) {
//         return false;
//     }
//
//     int countOfDigit = getCountOfDigit(number);
//
//     if (countOfDigit == 1) {
//         return true;
//     }
//
//
//     int leftDivider{1};
//     for (int i{1}; i < countOfDigit; i++) {
//         leftDivider *= 10;
//     }
//     for (size_t i{0}; i < countOfDigit / 2; i++) {
//         int rightDigit = number % 10;
//         int leftDigit = number / leftDivider;
//
//         if (rightDigit != leftDigit) {
//             return false;
//         }
//
//         number = number - rightDigit;
//         number %= leftDivider;
//         number /= 10;
//     }
//     return true;
// }


bool isPalindrome(int number)
{
    if (number < 0) return false;
    int num = number;
    int digits = getCountOfDigit(num);
    int po = pow(10, digits - 1);
    int newNumer{0};
    for (int i{0}; i < digits; i++)
    {
        int digit = num % 10;
        num = (num - digit) / 10;
        newNumer = newNumer + digit * po;
        po /= 10;
    }
    if (newNumer == number)
    {
        return true;
    }
    return false;
}


int sumOfPalindromeElements(const int* array, int n, int a, int b)
{
    int sum{0};
    for (const int* p{array}; p < array + n; p++)
    {
        if (*p > a && *p < b)
        {
            if (isPalindrome(*p))
            {
                sum += *p;
            }
        }
    }
    return sum;
}
