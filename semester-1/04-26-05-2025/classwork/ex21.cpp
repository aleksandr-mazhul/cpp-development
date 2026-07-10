
#include <iostream>
#include <ostream>
using namespace std;

int main()
{
    int i{0};
    int sum{0};
    while (i <= 100)
    {
        sum += i;
        i++;
    }
    cout << "Sum of numbers from 1 to 100:" << sum;
}
