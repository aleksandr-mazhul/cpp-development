#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
using namespace std;

double funcI(int n);

void test_funcI();

void test_single_funcI(int n, double expected);

int main()
{
    test_funcI();
}

double funcI(int n)
{
    double total_sum{0};
    double sin_sum{0};
    for (int i{1}; i <= n; ++i)
    {
        double range_rad = i * M_PI / 180.;
        sin_sum += sin(range_rad);
        total_sum += 1. / sin_sum;
    }
    return total_sum;
}

void test_funcI()
{
    test_single_funcI(6, 98.23879465320995);
    test_single_funcI(10, 104.20325304917145);
    test_single_funcI(100, 113.7643137434921);
}

void test_single_funcI(int n, double expected)
{
    cout << (abs(funcI(n) - expected) <= 0.00001 ? "passed" : "failed") << endl;
}
