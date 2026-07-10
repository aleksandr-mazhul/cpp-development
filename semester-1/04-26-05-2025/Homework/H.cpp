#include <iostream>
#include <cmath>
using namespace std;

double funcH(int n);

void test_funcH();

void test_single_funcH(int n, double expected);

int main()
{
    test_funcH();
}

double funcH(int n)
{
    double res{0};
    for (int i = 1; i <= n; i++)
    {
        res = sqrt(res + 2);
    }
    return res;
}

void test_funcH()
{
    test_single_funcH(6, 1.9993976373924085);
    test_single_funcH(10, 1.9999976469034038);
    test_single_funcH(100, 2);
    test_single_funcH(1000000, 2);
    test_single_funcH(10000000, 2);
}

void test_single_funcH(int n, double expected)
{
    cout << (abs(funcH(n) - expected) <= 0.00001 ? "passed" : "failed") << endl;
}




