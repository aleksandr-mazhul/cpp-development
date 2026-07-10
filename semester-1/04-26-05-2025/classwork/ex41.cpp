#include <iostream>
using namespace std;

int main()
{
    for (int i = 1; i <= 20; i++)
    {
        if (i % 2 == 0)
        {
            break;
        }
        cout << "Found first even number: " << i + 1 << endl;
    }
}
