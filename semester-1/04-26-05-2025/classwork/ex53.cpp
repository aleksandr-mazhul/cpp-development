#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int first{0}, res{0};
    for (int i = 0; i <= 10; i++)
    {
        res = pow(2, first);
        cout << "2^" << i << " = " << res << endl;
        first++;
    }
}
