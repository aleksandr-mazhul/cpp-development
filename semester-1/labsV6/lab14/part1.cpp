#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

double sumUser(double, double);

void horizontalLine();

int main()
{
    double x{}, eps{};
    while (true)
    {
        cout << "enter x and precision: " << endl;
        cin >> x >> eps;

        if (fabs(x) < 1 && eps < 0.05 && eps > 0)
        {
            break;
        }
        cout << "the parameters are entered incorrectly try again: " << endl;
    }


    horizontalLine();

    cout << string(4, ' ')
        << setw(10) << left << "x"
        << setw(20) << left << "precision"
        << setw(40) << left << "iteratively calculated value"
        << setw(30) << left << "values of the built-in function" << endl;


    horizontalLine();

    cout << string(4, ' ')
        << setw(10) << left << x
        << setw(20) << left << eps
        << setw(40) << left << sumUser(x, eps)
        << setw(30) << left << pow((1 + x), (-2.5)) << endl;

    horizontalLine();


    return 0;
}

double sumUser(double x, double eps)
{
    double sum{1}, term{1};
    for (int i{1}; fabs(term) > eps; i++)
    {
        term *= -(2 * i + 3) * x / (2 * i);
        sum += term;
    }
    return sum;
}


void horizontalLine()
{
    cout << "+" << string(10, '-')
        << "+" << string(17, '-')
        << "+" << string(37, '-')
        << "+" << string(43, '-') << "+" << endl;
}
