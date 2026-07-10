#include <iostream>
#include <cmath>
using namespace std;

double funcE(int n);

void test_funcE();

void test_single_funcE(int n, double expected);

int main()
{
    test_funcE();
}

double funcE(int n)
{
    double sum{0};
    for (int i{1}; i <= n; i++)
    {
        sum += 1. / ((2. * i + 1.) * (2. * i + 1.));
    }
    return sum;
}

void test_funcE()
{
    test_single_funcE(6, 0.19804657596199388);
    test_single_funcE(10, 0.21098888481753328);
    test_single_funcE(100, 0.23122532283135178);
    test_single_funcE(1000000, 0.23370030013643212);
    test_single_funcE(10000000, 0.23370052513612405);
}

void test_single_funcE(int n, double expected)
{
    // Исправлено: fancE → funcE
    cout << (abs(funcE(n) - expected) <= 0.00001 ? "passed" : "failed") << endl;
}
