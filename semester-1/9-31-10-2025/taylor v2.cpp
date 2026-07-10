#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

double factorial(int n);
double taylorSin(double x, int terms);
double taylorSin(double x, double epsilon, int& k);
double taylorCos(double x, double epsilon, int& k);
void testSinFunction();
bool compareWithLibrary(double x, double ourResult, double tolerance = 0.001);
void printSineTable(double from, double to, double step, double epsilon = 1e-9);
void printCoseTable(double from, double to, double step, double epsilon = 1e-9);
bool almostEqual(double a, double b, double epsilon = 1e-9);

int main()
{
    double from, to, step;
    std::cout << "\nEnter interval [from, to] and step (e.g., 0 3.14159 0.314159): ";
    std::cin >> from >> to >> step;
    printSineTable(from, to, step, 1e-20);
    printCoseTable(from, to, step, 1e-20);
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
    double term = x;
    double result = term;
    for (int n = 1; n <= terms; n++)
    {
        term *= -x * x / (2 * n) / (2 * n + 1);
        result += term;
    }
    return result;
}

double taylorSin(double x, double epsilon, int& k)
{
    double term = x;
    double result = term;
    k = 1;
    while (true)
    {
        term *= -x * x / (2 * k) / (2 * k + 1);
        if (std::fabs(term) <= epsilon)
        {
            break;
        }
        result += term;
        ++k;
    }
    return result;
}

void testSinFunction()
{
    std::cout << "Testing taylorSin() function..." << std::endl;

    double result1 = taylorSin(0, 10);
    std::cout << "Test 1 - sin(0): ";
    if (compareWithLibrary(0, result1, 0.0001))
    {
        std::cout << "PASSED ✓" << std::endl;
    }
    else
    {
        std::cout << "FAILED ✗" << std::endl;
    }

    double result2 = taylorSin(M_PI / 2, 15);
    std::cout << "Test 2 - sin(π/2): ";
    if (compareWithLibrary(M_PI / 2, result2, 0.01))
    {
        std::cout << "PASSED ✓" << std::endl;
    }
    else
    {
        std::cout << "FAILED ✗" << std::endl;
    }

    double result3 = taylorSin(M_PI, 15);
    std::cout << "Test 3 - sin(π): ";
    if (compareWithLibrary(M_PI, result3, 0.01))
    {
        std::cout << "PASSED ✓" << std::endl;
    }
    else
    {
        std::cout << "FAILED ✗" << std::endl;
    }

    double result4 = taylorSin(M_PI / 6, 15);
    std::cout << "Test 4 - sin(π/6): ";
    if (compareWithLibrary(M_PI / 6, result4, 0.01))
    {
        std::cout << "PASSED ✓" << std::endl;
    }
    else
    {
        std::cout << "FAILED ✗" << std::endl;
    }

    double result5 = taylorSin(-M_PI / 4, 15);
    std::cout << "Test 5 - sin(-π/4): ";
    if (compareWithLibrary(-M_PI / 4, result5, 0.01))
    {
        std::cout << "PASSED ✓" << std::endl;
    }
    else
    {
        std::cout << "FAILED ✗" << std::endl;
    }

    std::cout << "\n=== Accuracy test depending on number of terms ===" << std::endl;
    double testAngle = M_PI / 3;
    double libraryValue = std::sin(testAngle);
    std::cout << "Angle: " << testAngle << " radians" << std::endl;
    std::cout << "Library value: " << libraryValue << std::endl;
    std::cout << "Number of terms | Our result | Error" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    for (int terms = 5; terms <= 20; terms += 5)
    {
        double ourValue = taylorSin(testAngle, terms);
        double error = std::fabs(ourValue - libraryValue);
        std::cout << std::setw(15) << terms << " | "
            << std::setw(12) << std::fixed << std::setprecision(6) << ourValue
            << " | " << std::scientific << error << std::endl;
    }
}

bool compareWithLibrary(double x, double ourResult, double tolerance)
{
    double libraryResult = std::sin(x);
    return almostEqual(ourResult, libraryResult, tolerance);
}

void printSineTable(double from, double to, double step, double epsilon)
{
    if (step <= 0 || to < from)
    {
        std::cout << "Invalid interval or step." << std::endl;
        return;
    }

    std::cout << "\n=== Sine table on interval ===" << std::endl;
    std::cout << std::left
        << std::setw(14) << "x"
        << std::setw(16) << "taylorSin(x)"
        << std::setw(16) << "std::sin(x)"
        << std::setw(16) << "abs error"
        << std::setw(7) << "terms" << std::endl;
    std::cout << std::string(69, '-') << std::endl;

    for (double x = from; x <= to + 1e-12; x += step)
    {
        int k = 0;
        double our = taylorSin(x, epsilon, k);
        double lib = std::sin(x);
        double err = std::fabs(our - lib);

        std::cout << std::fixed << std::setprecision(6)
            << std::setw(14) << x
            << std::setw(16) << our
            << std::setw(16) << lib
            << std::scientific << std::setprecision(6)
            << std::setw(16) << err
            << std::setw(7) << k
            << std::defaultfloat
            << std::endl;
    }
}

bool almostEqual(double a, double b, double epsilon)
{
    return std::fabs(a - b) <= epsilon * std::max(1.0, std::max(std::fabs(a), std::fabs(b)));
}

double taylorCos(double x, double epsilon, int& k)
{
    double term = 1.0;
    double result = term;
    int n = 1;
    while (true)
    {
        term *= -x * x / (2 * n - 1) / (2 * n);
        if (std::fabs(term) <= epsilon)
        {
            break;
        }
        result += term;
        ++n;
    }
    k = n;
    return result;
}

void printCoseTable(double from, double to, double step, double epsilon)
{
    if (step <= 0 || to < from)
    {
        std::cout << "Invalid interval or step." << std::endl;
        return;
    }

    std::cout << "\n=== Cosine table on interval ===" << std::endl;
    std::cout << std::left
        << std::setw(14) << "x"
        << std::setw(16) << "taylorCos(x)"
        << std::setw(16) << "std::cos(x)"
        << std::setw(16) << "abs error"
        << std::setw(7) << "terms" << std::endl;
    std::cout << std::string(69, '-') << std::endl;

    for (double x = from; x <= to + 1e-12; x += step)
    {
        int k = 0;
        double our = taylorCos(x, epsilon, k);
        double lib = std::cos(x);
        double err = std::fabs(our - lib);

        std::cout << std::fixed << std::setprecision(6)
            << std::setw(14) << x
            << std::setw(16) << our
            << std::setw(16) << lib
            << std::scientific << std::setprecision(6)
            << std::setw(16) << err
            << std::setw(7) << k
            << std::defaultfloat
            << std::endl;
    }
}
