#include <iostream>
using namespace std;

int power(int base, int exp);

int getCountOfDigit(int number);

int sumOfFigureIncludePow(int array[], int position);

bool isArmstrong(int array[], int position);

int sumEllementsOfArray(int array[], int N);

int sumOfArmstrongAumbers(int array[], int N);

void tests(int array[], int N, int expected);

void printTests();

int* empty = nullptr;

int a1[] = {10, 20, 99, 123, 200};
int a2[] = {0, 1, 2, 5, 9};
int a3[] = {153, 370, 371, 407};
int a4[] = {5, 10, 153, 200, 371, 99};
int a5[] = {-153, -10, 0, 1, 370};
int a6[] = {153, 153, 153};
int a7[] = {9474, 54748, 92727, 93084};
int a8[] = {100, 200, 300, 400, 500, 600};
int a9[] = {0, 1, 2, 9, 10, 153, 154, 370, 371, 407, 500};

int main()
{
    printTests();
    return 0;
}

int power(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++)
        result *= base;
    return result;
}

int getCountOfDigit(int number)
{
    if (number == 0) return 1;
    if (number < 0) number = -number;

    int count = 0;
    while (number > 0)
    {
        count++;
        number /= 10;
    }
    return count;
}

int sumOfFigureIncludePow(int array[], int position)
{
    int number = array[position];
    if (number < 0) number = -number;

    int digits = getCountOfDigit(number);
    int sum = 0;

    while (number > 0)
    {
        int figure = number % 10;
        sum += power(figure, digits);
        number /= 10;
    }
    return sum;
}

bool isArmstrong(int array[], int position)
{
    if (array[position] < 0) return false;
    return sumOfFigureIncludePow(array, position) == array[position];
}

int sumEllementsOfArray(int array[], int N)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
        sum += array[i];
    return sum;
}

int sumOfArmstrongAumbers(int array[], int N)
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        if (isArmstrong(array, i))
            sum += array[i];
    }
    return sum;
}

void tests(int array[], int N, int expected)
{
    cout << (sumOfArmstrongAumbers(array, N) == expected ? "Passed" : "Failed") << endl;
}

void printTests()
{
    // tests(empty, 0, 0);
    tests(a1, 5, 0);
    tests(a2, 5, 17);
    tests(a3, 4, 1301);
    tests(a4, 6, 529);
    tests(a5, 5, 371);
    tests(a6, 3, 459);
    tests(a7, 4, 250033);
    tests(a8, 6, 0);
    tests(a9, 11, 1313);
}
