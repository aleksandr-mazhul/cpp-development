#include <iostream>
using namespace std;

int main()
{
    int i{1};
    int factorial{1};
    while (i <= 5)
    {
        factorial *= i;
        i++;
    }
    cout << "Factorial of 5:" << factorial << endl;
}
