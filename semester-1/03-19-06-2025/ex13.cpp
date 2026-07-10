#include <iostream>
using namespace std;

int main()
{
    int i{1};
    do
    {
        cout << i << (i == 10 ? ". " : ", ");
        i += 3;
    }
    while (i <= 10);
}




