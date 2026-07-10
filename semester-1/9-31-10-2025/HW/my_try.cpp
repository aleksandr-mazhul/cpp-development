#include <iostream>
#include <cmath>
using namespace std;

double taylorSin(double x, int terms);

double taylorSin(double x, double epsilon, int& termsUsed);


int main()
{
    while (true)
    {
        int mod{};
        cout << "Enter a number to select the mode.: " << endl;
        cout << "1 - number of terms\n";
        cout << "2 - epsilon mode\n";
        cin >> mod;
        if (mod == 1)
        {
            double x{};
            cout << "Enter x ";
            cin >> x;
            int terms{};
            cout << "Enter the number of terms: ";
            cin >> terms;
            cout << "taylorSin( " << "corner: " << x << " , " << "terms: " << terms << " ): " << taylorSin(x, terms) <<
                endl;
            cout << "sin(x) library: " << sin(x) << endl;

            break;
        }
        else if (mod == 2)
        {
            int termsUsed{};
            double x{};
            cout << "Enter x ";
            cin >> x;
            double epsilon{};
            cout << "Enter epsilon: " << endl;
            cin >> epsilon;
            cout << "taylorSin( " << "corner: " << x << " , " << "epsilon: " << epsilon << " ): " << taylorSin(
                x, epsilon, termsUsed) << endl;
            cout << "sin(x) library: " << sin(x) << endl;
            cout << "terms used: " << termsUsed << endl;
            break;
        }
        else
        {
            cout << "select the mode" << endl;
        }
    }
    return 0;
}


double taylorSin(double x, int terms)
{
    double term = x;
    double result = term;
    for (int i{0}; i <= terms - 2; i++)
    {
        term *= (-(x * x) / (2 * i + 2) / (2 * i + 3));
        result += term;
    }
    return result;
}


double taylorSin(double x, double epsilon, int& termsUsed)
{
    double term = x;
    double result = term;
    termsUsed = 1;
    int i{0};
    while (fabs(term) > epsilon)
    {
        term *= (-(x * x) / (2 * i + 2) / (2 * i + 3));
        result += term;
        i++;
        termsUsed++;
    }
    return result;
}
