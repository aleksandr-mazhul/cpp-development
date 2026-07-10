#include <iostream>
#include <cmath>
using namespace std;
using std::boolalpha;

bool insideZone(double, double);

void testPoints();

int main()
{
    testPoints();
    return 0;
}


bool insideZone(double x, double y)
{
    const double MIN_RADIUS{1};
    const double MAX_RADIUS{3};

    double distance = sqrt(x * x + y * y);

    bool isCircle = distance < MAX_RADIUS;
    bool isUpperHalf = y >= 0;
    bool isLeftHalf = x <= 0;
    bool isMoreThenMin_RADIUS = distance >= MIN_RADIUS;

    return isCircle && isUpperHalf && isLeftHalf && isMoreThenMin_RADIUS;
}

void testPoints()
{
    cout << "Testing true" << endl;

    cout << "(-2.0, 1.5): " << boolalpha << insideZone(-2.0, 1.5) << endl;
    cout << "(-1.0, 2.0): " << insideZone(-1.0, 2.0) << endl;
    cout << "(0.0, 1.5): " << insideZone(0.0, 1.5) << endl;
    cout << "(-1.5, 0.0): " << insideZone(-1.5, 0.0) << endl;
    cout << "(-0.71, 0.71): " << insideZone(-0.71, 0.71) << endl;
    cout << "(-2.0, 0.5): " << insideZone(-2.0, 0.5) << endl;
    cout << "(-1.2, 1.8): " << insideZone(-1.2, 1.8) << endl;
    cout << "(-0.5, 1.8): " << insideZone(-0.5, 1.8) << endl;
    cout << "(-2.5, 1.0): " << insideZone(-2.5, 1.0) << endl;
    cout << "(-1.8, 1.8): " << insideZone(-1.8, 1.8) << endl;

    cout << "Testing false" << endl;

    cout << "(-0.5, 0.5): " << insideZone(-0.5, 0.5) << endl;
    cout << "(-2.0, -1.0): " << insideZone(-2.0, -1.0) << endl;
    cout << "(1.0, 1.0): " << insideZone(1.0, 1.0) << endl;
    cout << "(-2.9, 1.5): " << insideZone(-2.9, 1.5) << endl;
    cout << "(0.0, 0.5): " << insideZone(0.0, 0.5) << endl;
    cout << "(-0.5, -0.5): " << insideZone(-0.5, -0.5) << endl;
    cout << "(2.0, 2.0): " << insideZone(2.0, 2.0) << endl;
    cout << "(-3.0, 0.0): " << insideZone(-3.0, 0.0) << endl;
    cout << "(0.0, 3.0): " << insideZone(0.0, 3.0) << endl;
    cout << "(-2.8, -0.5): " << insideZone(-2.8, -0.5) << endl;
    cout << "(1.5, -1.5): " << insideZone(1.5, -1.5) << endl;
    cout << "(-1.0, -2.0): " << insideZone(-1.0, -2.0) << endl;
    cout << "(2.5, 0.0): " << insideZone(2.5, 0.0) << endl;
    cout << "(0.0, 0.9): " << insideZone(0.0, 0.9) << endl;
}
