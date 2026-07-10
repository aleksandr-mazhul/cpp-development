#include <iostream>
using namespace std;

int sumOfSquaredDigits(int number);

bool isLuckyNumber(int number);

int findCertainLuckyNumber(int array[], int n, int a, int b, int k);

int main()
{
    int array[]{2, 4, 5, 7, 8, 10, 17, 19, 7, 20, 65, 324, 2, 53, 54, 6, 57, 68, 67, 89, 35, 2, 4, 7, 6, 12, 31, 31};
    int n = sizeof(array) / sizeof(array[0]);
    cout << findCertainLuckyNumber(array, n, 1, 360, 1);
}

int sumOfSquaredDigits(int number)
{
    int sum{0};
    while (number != 0)
    {
        int digit = number % 10;
        number = (number - digit) / 10;
        sum = sum + digit * digit;
    }
    return sum;
}

bool isLuckyNumber(int number)
{
    while (true)
    {
        int x = sumOfSquaredDigits(number);
        if (x == 1)
        {
            return true;
        }
        if (x == 4)
        {
            return false;
        }
        if (x == 0)
        {
            return false;
        }
        number = x;
    }
}


int findCertainLuckyNumber(int array[], int n, int a, int b, int k)
{
    for (int *p{array}, counter{0}; p < array + n; p++)
    {
        if (isLuckyNumber(*p) && *p > a && *p < b)
        {
            counter++;
            if (counter == k)
            {
                return *p;
            }
        }
    }
    return 0;
}
