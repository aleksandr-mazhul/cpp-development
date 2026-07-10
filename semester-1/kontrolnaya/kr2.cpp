#include  <iostream>
using namespace std;

void initArrayFibonacci(int* array, int N);

int fibonacci(int n);

int sumArrayFibonacci(int* array, int from, int to, int N);

void testFibonacci(int* array, int N);

int main()
{
    int constexpr N{40};
    int array[N]{0};
    testFibonacci(array, N);
}

void initArrayFibonacci(int* array, int N)
{
    for (int i = 0; i < N; i++)
    {
        array[i] = fibonacci(i);
    }
}

int fibonacci(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int sumArrayFibonacci(int* array, int from, int to, int N)
{
    int sum{0};
    for (int i = 0; i < N; i++)
    {
        if (array[i] >= from && array[i] <= to)
        {
            sum += array[i];
        }
    }
    return sum;
}


void testFibonacci(int* array, int N)
{
    initArrayFibonacci(array, N);
    cout << ((sumArrayFibonacci(array, 1, 40, N) == 88) ? "passed" : "failed") << endl;
    cout << ((sumArrayFibonacci(array, 5, 100, N) == 225) ? "passed" : "failed") << endl;
    cout << ((sumArrayFibonacci(array, 150, 180, N) == 0) ? "passed" : "failed") << endl;
    cout << ((sumArrayFibonacci(array, 40, 57, N) == 55) ? "passed" : "failed") << endl;
    cout << ((sumArrayFibonacci(array, 79, 200, N) == 233) ? "passed" : "failed") << endl;
}
