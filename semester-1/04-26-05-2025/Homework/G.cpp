#include <iostream>
#include <cmath>
using namespace std;

double funcG(int n);

void test_funcG();

void test_single_funcG(int n, double expected);

int main()
{
    test_funcG();
}

double funcG(int n)
{
    double sum{0};
    double fac{1};
    double res{0};
    for (int i = 1; i <= n; i++)
    {
        fac *= i;
        sum += 1. / i;
        res += fac / sum;
    }
    return res;
}

void test_funcG()
{
    test_single_funcG(6, 363.55835615201624);
    test_single_funcG(10, 1384350.0519936203);
    test_single_funcG(100, 1.8173121424936406E+157);
}

void test_single_funcG(int n, double expected)
{
    cout << (abs(funcG(n) - expected) <= 0.00001 ? "passed" : "failed") << endl;
}
