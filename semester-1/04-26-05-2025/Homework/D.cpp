#include <iostream>
#include <cmath>
using namespace std;

double funcD(int n);

void test_funcD();

void test_single_funcD(int n, double expected);

int main()
{
    test_funcD();
}

double funcD(int n)
{
    double sum{};
    double chenger{1};
    for (int i{1}; i <= n; i++)
    {
        sum += chenger / (i * (i + 1.0));
        chenger *= -1;
    }
    return sum;
}

void test_funcD()
{
    test_single_funcD(6, 0.3761904761904762);
    test_single_funcD(10, 0.3821789321789322);
    test_single_funcD(100, 0.3862453487194004);
    test_single_funcD(1000000, 0.38629436111938714);
    test_single_funcD(10000000, 0.38629436111988125);
}

void test_single_funcD(int n, double expected)
{
    cout << (abs(funcD(n) - expected) <= 0.000001 ? "passed" : "failed") << endl;
}
