#include <iostream>
#include <climits>

using namespace std;

int getCountOfDigits(long long number);


int main()
{
    cout << LLONG_MAX << endl;
    cout << LLONG_MIN << endl;
    cout << getCountOfDigits(LLONG_MAX) << endl;
    cout << getCountOfDigits(LLONG_MIN);
}

int getCountOfDigits(long long number)
{
    if (!number)
    {
        return 1;
    }

    int count{0};
    while (number)
    {
        count++;
        number /= 10;
    }

    return count;
}
