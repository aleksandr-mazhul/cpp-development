#include <iostream>
#include <cmath>

using namespace std;

double operation(double x);

int main()
{
    double y;
    cout << "Enter a floating point number: " << endl;
    cin >> y;

    cout << "result of functoin work:" << operation(y) << endl;
    return 0;
}

double operation(double x)
{
    int intPart{int(x < 0 ? x - 1 : x)};
    double fractPart{x - intPart};
    if (intPart < 10 * fractPart)
    {
        return x / 10;
    }
    else return intPart;
}
