#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

int getCountOfDigits(long long number);

bool isPalindrom(long long number);

int main()
{
    cout << (isPalindrom(-163473226) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(32589706) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(0) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(5) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(-3) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(1001) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(-400004) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(909909) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(500505) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(100001) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(LLONG_MAX) ? "PALINDROM" : "NOT") << endl;
    cout << (isPalindrom(LLONG_MIN) ? "PALINDROM" : "NOT") << endl;
}

int getCountOfDigits(long long number)
{
    if (number == 0)
    {
        return 1;
    }

    // или (!number) {
    // return 1;
    // }

    int count{};

    while (number)
    {
        count++;
        number /= 10;
    }
    return count;
}

bool isPalindrom(long long number)
{
    if (number > -10 && number < 10)
    {
        return true;
    }

    number = number < 0 ? abs(number) : number; // ? LLONG_MIN

    int count(getCountOfDigits(number)), degree(pow(10, count - 1));

    while (number)
    {
        int first(number / degree), last(number % 10);
        if (first != last)
        {
            return false;
        }
        number %= degree;
        number /= 10;
        degree /= 100;
    }
    return true;
}
