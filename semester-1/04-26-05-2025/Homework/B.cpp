#include <iostream>
#include <cmath>
using namespace std;
double fancC(int n);
void test_fancB();
void test_single_fancB(int n, double expected);

int main()
{
    test_fancB();
}

double fancC(int n)
{
    double product{1};
    for (int i = 1; i <= n; ++i)
    {
        product *= 1.0 + (1.0 / i / i);
    }
    return product;
}

void test_fancB()
{
    test_single_fancB(6, 3.154706790123457);
    test_single_fancB(10, 3.342847116573682);
    test_single_fancB(100, 3.639682294531309);
    test_single_fancB(1000000, 3.676074234300874);
    test_single_fancB(10000000, 3.6760775427785917);
}

void test_single_fancB(int n, double expected)
{
    cout << (abs(fancC(n) - expected) <= 0.0001 ? "passed" : "failed") << endl;
}

