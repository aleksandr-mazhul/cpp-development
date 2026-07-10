#include <iostream>
#include <cmath>
using namespace std;

double operation(int m, int n);

int main()
{
    int m{};
    int n{};
    cout << "enter two different numbers" << endl;
    while (true)
    {
        cin >> n >> m;


        if ((n == 0 && m == 0) || n == m)
        {
            cout << "enter the correct numbers" << endl;
        }
        else
        {
            break;
        }
    }
    cout << "result of functoin work:" << operation(m, n) << endl;
    return 0;
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
