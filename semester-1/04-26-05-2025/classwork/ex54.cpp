#include <complex>
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int sum{0};
    for (int i = 0; i <= 10; i++)
    {
        sum += pow(i, 2);
    }
    cout << "Sum of squares from 1 to 10: " << sum << endl;
}
