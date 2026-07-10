#include <iostream>
using namespace std;

int main()
{
    int n{};
    while (true)
    {
        cout << "Enter positive number: ";
        cin >> n;
        if (n > 0)
        {
            break;
        }
        cout << "invalid input" << endl;
    }

    int sum{};
    for (int i = 1; i <= n; i++)
    {
        sum += i;
        cout << i << (i == n ? " = " : " + ");
    }
    cout << sum << endl;
}
