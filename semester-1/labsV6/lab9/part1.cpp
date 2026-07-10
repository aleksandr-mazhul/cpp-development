#include <iostream>
#include <cmath>
using namespace std;
using std::locale;
using std::boolalpha;

bool insideZone(double, double);

int main()
{
    double xCoord{}, yCoord{};
    cout << "enter a pair of coordinates" << endl;
    cin >> xCoord >> yCoord;
    cout << "the point hit the circle?"
        << boolalpha
        << insideZone(xCoord, yCoord);
    return 0;
}

bool insideZone(double x, double y)
{
    const double R{3};
    return sqrt(x * x + y * y) < R;
}
