#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

constexpr double PI = 3.14159265358979323846;

double factorial(int n);

double taylorSin(double x, int terms);

double taylorSin(double x, double epsilon);

double taylorSin1(double x, int terms);

void testSinFunction();

bool compareWithLibrary(double x, double ourResult, double tolerance = 0.001);

void printSineTable(double from, double to, double step, int terms);

bool almostEqual(double a, double b, double epsilon = 1e-9);

int main()
{
    cout << "=== Sine calculation using Taylor series ===" << endl;

    int terms;
    cout << "Enter number of series terms (recommended 10-15): ";
    cin >> terms;

    cout << "\n=== Running tests ===" << endl;
    testSinFunction();

    double from, to, step;
    cout << "\nEnter interval [from, to] and step (e.g., 0 3.14159 0.314159): ";
    cin >> from >> to >> step;
    printSineTable(from, to, step, terms);

    return 0;
}

double factorial(int n)
{
    if (n <= 1)
    {
        return 1.0;
    }
    double result = 1.0;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

double taylorSin(double x, int terms)
{
    double result = 0.0;
    double term = x;
    for (int n = 1; n <= terms; n++)
    {
        result += term;
        term *= -x * x / (2 * n) / (2 * n + 1);
    }
    return result;
}

double taylorSin(double x, double epsilon)
{
    double result = 0.0;
    double term = x;
    int n = 1;
    while (fabs(term) > epsilon)
    {
        result += term;
        term *= -x * x / (2 * n) / (2 * n + 1);
        n++;
    }
    return result;
}

double taylorSin1(double x, int terms)
{
    double result = 0.0;
    for (int n = 0; n < terms; n++)
    {
        double term = pow(-1.0, n) * pow(x, 2 * n + 1) / factorial(2 * n + 1);
        result += term;
    }
    return result;
}

void testSinFunction()
{
    cout << "Testing taylorSin() function..." << endl;

    double result1 = taylorSin(0, 10);
    cout << "PASSED ✓" << endl;
    if (compareWithLibrary(0, result1, 0.0001))
    {
        cout << "FAILED ✗" << endl;
        cout << "Test 1 - sin(0): ";
    }
    else
    {
    }

    double result2 = taylorSin(PI / 2, 15);
    cout << "Test 2 - sin(π/2): ";
    if (compareWithLibrary(PI / 2, result2, 0.01))
    {
        cout << "PASSED ✓" << endl;
    }
    else
    {
        cout << "FAILED ✗" << endl;
    }

    double result3 = taylorSin(PI, 15);
    cout << "Test 3 - sin(π): ";
    if (compareWithLibrary(PI, result3, 0.01))
    {
        cout << "PASSED ✓" << endl;
    }
    else
    {
        cout << "FAILED ✗" << endl;
    }

    double result4 = taylorSin(PI / 6, 15);
    cout << "Test 4 - sin(π/6): ";
    if (compareWithLibrary(PI / 6, result4, 0.01))
    {
        cout << "PASSED ✓" << endl;
    }
    else
    {
        cout << "FAILED ✗" << endl;
    }

    double result5 = taylorSin(-PI / 4, 15);
    cout << "Test 5 - sin(-π/4): ";
    if (compareWithLibrary(-PI / 4, result5, 0.01))
    {
        cout << "PASSED ✓" << endl;
    }
    else
    {
        cout << "FAILED ✗" << endl;
    }

    cout << "\n=== Accuracy test depending on number of terms ===" << endl;
    double testAngle = PI / 3;
    double libraryValue = sin(testAngle);

    cout << "Angle: " << testAngle << " radians" << endl;
    cout << "Library value: " << libraryValue << endl;
    cout << "Number of terms | Our result   | Error" << endl;
    cout << "----------------------------------------------" << endl;

    for (int terms = 5; terms <= 20; terms += 5)
    {
        double ourValue = taylorSin(testAngle, terms);
        double error = fabs(ourValue - libraryValue);
        cout << setw(15) << terms << " | "
            << setw(12) << fixed << setprecision(6) << ourValue
            << " | " << scientific << error << endl;
    }
}

bool compareWithLibrary(double x, double ourResult, double tolerance)
{
    double libraryResult = sin(x);
    return almostEqual(ourResult, libraryResult, tolerance);
}

void printSineTable(double from, double to, double step, int terms)
{
    if (step <= 0 || to < from)
    {
        cout << "Invalid interval or step." << endl;
        return;
    }

    cout << "\n=== Sine table on interval ===" << endl;
    cout << left
        << setw(14) << "x"
        << setw(16) << "taylorSin(x)"
        << setw(16) << "std::sin(x)"
        << setw(16) << "abs error"
        << endl;
    cout << string(62, '-') << endl;

    for (double x = from; x <= to + 1e-12; x += step)
    {
        double our = taylorSin(x, terms);
        double lib = sin(x);
        double err = fabs(our - lib);

        cout << fixed << setprecision(6)
            << setw(14) << x
            << setw(16) << our
            << setw(16) << lib
            << scientific << setprecision(6)
            << setw(16) << err
            << defaultfloat
            << endl;
    }
}

bool almostEqual(double a, double b, double epsilon)
{
    return fabs(a - b) <= epsilon * max(1.0, max(fabs(a), fabs(b)));
}
