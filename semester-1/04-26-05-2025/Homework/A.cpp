#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double fancA(int n);

void test_fancA();

void test_single_fancA(int n, double expected);

int main()
{
    test_fancA();
}

double fancA(int n)
{
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += 1.0 / i;
    }
    return sum;
}

void test_fancA()
{
    test_single_fancA(6, 2.4499999999999997);
    test_single_fancA(10, 2.9289682539682538);
    test_single_fancA(100, 5.187377517639621);
    test_single_fancA(1000000, 14.392726722864989);
    test_single_fancA(10000000, 16.695311365857272);
}

void test_single_fancA(int n, double expected)
{
    cout << (abs(fancA(n) - expected) <= 0.0001 ? "passed" : "failed") << endl;
}
