#include <iostream>
using namespace std;

int main()
{
    int sum{0};
    for (int i = 0; i <= 100; i++)
    {
        sum += i;
        if (sum <= 1000)
        {
            break;
        }
        cout << " Sum: " << sum << endl;
        cout << "stoped at number: " << i << endl;
    }
    return 0;
}
