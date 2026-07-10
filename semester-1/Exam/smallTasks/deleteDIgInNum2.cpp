#include <cmath>
#include <iostream>
using namespace std;

void deleteOllInclusionsOfDig(int* number, int d);

int main()
{
    int number = 23982084;
    deleteOllInclusionsOfDig(&number, 2);
    cout << number;
}

void deleteOllInclusionsOfDig(int* number, int d)
{
    int x = *number;
    int newNumber{0};
    int digit{0};
    int counter{1};

    while (x != 0)
    {
        digit = x % 10;
        if (digit != d)
        {
            newNumber = newNumber + digit * counter;
            counter *= 10;
        }
        x = (x - digit) / 10;
    }
    *number = newNumber;
}
