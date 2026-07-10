#include <iostream>
using namespace std;

int power(int base, int exp);

int getCountOfDigit(int number);

int sumOfFigureIncludePow(int array[], int position);

bool isArmstrong(int array[], int N);

int sumEllementsOfArray(int array[], int N);

int sumOfArmstrongAumbers(int array[], int N);

void tests(int array[], int N);

// bool isarrayOfArmstrongNumbers(int array[], int N);


int main()
{
    int array0[]{0, 1, 2, 5, 9};
    int N0 = 5;

    int array1[]{10, 20, 99, 123, 200};
    int N1 = 5;

    int array2[]{0, 1, 2, 5, 9};
    int N2 = 5;

    int array3[]{153, 370, 371, 407};
    int N3 = 4;

    int array4[]{5, 10, 153, 200, 371, 99};
    int N4 = 6;

    int array5[]{-153, -10, 0, 1, 370};
    int N5 = 5;
}


int power(int base, int exp)
{
    if (exp == 0) return 1;
    int result{1};
    for (int i = 1; i <= exp; i++)
    {
        result = base * result;
    }
    return result;
}

int getCountOfDigit(int number)
{
    int count = 0;
    if (number == 0)
        return 1;

    while (number != 0)
    {
        count++;
        number /= 10;
    }

    return count;
}


int sumOfFigureIncludePow(int array[], int position)
{
    int number = array[position];
    int figure = {0};
    int sum{0};

    for (int i = 1; i <= getCountOfDigit(array[position]); i++)
    {
        figure = number % 10;
        number /= 10;
        sum += power(figure, getCountOfDigit(number));
    }
    return sum;
}


bool isArmstrong(int array[], int N)
{
}


int sumEllementsOfArray(int array[], int N)
{
    int sum{0};
    for (int i = 0; i < N; i++)
    {
        sum += array[i];
    }
    return sum;
}


int sumOfArmstrongAumbers(int array[], int N)
{
    int sum{0};
    for (int i = 0; i < N; i++)
    {
        sum += sumOfFigureIncludePow(array, i);
    }
    return sum;
}

void tests(int array[], int N)
{
    sumOfArmstrongAumbers(array, N) == 0 ? cout << "Passed" << endl : cout << endl;
}
