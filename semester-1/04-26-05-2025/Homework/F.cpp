#include <iostream>
#include <cmath>
using namespace std;

double funcF(int n);

void test_funcF();

void test_single_funcF(int n, double expected);

int main()
{
    test_funcF();
}

double funcF(int n)
{
    double sum{0};
    int changer{-1};
    for (int i{1}; i <= n; i++)
    {
        sum += changer / (2. * i + 1.);
        changer *= -1;
    }
    return sum;
}

void test_funcF()
{
    test_single_funcF(6, -0.17906537906537906);
    test_single_funcF(10, -0.1919210476486018);
    test_single_funcF(100, -0.21212664973225237);
    test_single_funcF(1000000, -0.21460158660281903);
    test_single_funcF(10000000, -0.2146018116025734);
}

void test_single_funcF(int n, double expected)
{
    cout << (abs(funcF(n) - expected) <= 0.00001 ? "passed" : "failed") << endl;
}
