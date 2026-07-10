#include <iostream>
#include <cmath>
using namespace std;

double operation(int m, int n);

void test_operation();

int main()
{
    test_operation();
}

double operation(int m, int n)
{
    const double PI = 3.141592653589793;
    double M_on_N = static_cast<double>(m) / n;
    double N_on_M = static_cast<double>(n) / m;
    if (abs(M_on_N - PI) < abs(N_on_M - PI))
    {
        return m * 10;
    }
    else
    {
        return n * 2;
    }
}

void test_operation()
{
    cout << "Test 1 (22, 7): " << (operation(22, 7) == 220 ? "passed" : "FAILED") << endl;
    cout << "Test 2 (7, 22): " << (operation(7, 22) == 44 ? "passed" : "FAILED") << endl;
    cout << "Test 3 (355, 113): " << (operation(355, 113) == 3550 ? "passed" : "FAILED") << endl;
    cout << "Test 4 (19, 6): " << (operation(19, 6) == 190 ? "passed" : "FAILED") << endl;
    cout << "Test 5 (1, 100): " << (operation(1, 100) == 10 ? "passed" : "FAILED") << endl;
    cout << "Test 6 (-22, -7): " << (operation(-22, -7) == -220 ? "passed" : "FAILED") << endl;
}
