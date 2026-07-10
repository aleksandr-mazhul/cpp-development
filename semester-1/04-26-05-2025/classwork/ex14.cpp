#include <iostream>
using namespace std;

int main()
{
    for (int i = 1; i <= 19; i += 2)
    {
        cout << i << (i == 19 ? ". " : ", ");
    }
}
