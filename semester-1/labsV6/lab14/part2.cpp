#include <iostream>
# include <cmath>

using namespace std;

double sequence(unsigned);

double iterativeAddition(double);

int main()
{
    double eps;
    while (true)
    {
        cout << "enter  precision" << endl;
        cin >> eps;
        if (eps > 0)
        {
            break;
        }
        cout << "enter a positive epsilon" << endl;
    }

    cout << "the value of calculating the limit" << iterativeAddition(eps);
    return 0;
}

double iterativeAddition(double eps)
{
    double current{0}, next{0};
    int i{0};
    do
    {
        current = sequence(i);
        next = sequence(i + 1);
        i++;
    }
    while ((fabs((current) - next)) > eps);
    return current;
}


double sequence(unsigned n)
{
    return 1.0 / sqrt(2 * n + 5);
}
