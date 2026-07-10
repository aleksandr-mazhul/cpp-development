#include <iostream>
using namespace std;

int main()
{
    double x[]{1., 21., 13., 64., 5.};
    const int N{sizeof(x) / sizeof(double)};
    double sum{0};
    for (int i = 0; i < N; i++)
    {
        sum += x[i];
    }
    cout << "the arithmetic mean = " << sum / N << endl;
    return 0;
}
