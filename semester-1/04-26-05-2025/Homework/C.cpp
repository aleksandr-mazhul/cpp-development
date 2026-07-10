#include <iostream>
#include <cmath>
using namespace std;

double fancC(int n, int k);

void test_fancC();

void test_single_fancE(int n, int k, double expected);


int main()
{
    test_fancC();
}

double fancC(int n, int k)
{
    double sum{0};
    for (int i = 1; i <= n; ++i)
    {
        sum += 1 / pow(i, k);
    }
    return sum;
}

void test_fancC()
{
    test_single_fancE(6, 5, 1.036790389660494);
    test_single_fancE(10, 5, 1.0369073413446939);
    test_single_fancE(100, 5, 1.0369277526929555);
    test_single_fancE(1000000, 5, 1.036927755143338);
    test_single_fancE(10000000, 5, 1.036927755143338);
}

void test_single_fancE(int n, int k, double expected)
{
    cout << (abs(fancC(n, k) - expected) <= 0.00000001 ? "passed" : "failed") << endl;
}
