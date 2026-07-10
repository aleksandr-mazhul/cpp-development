#include <iostream>
using namespace std;

int main()
{
    for (int i = 2; i <= 20; i++)
    {
        bool prime{true};

        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                prime = false;
                break;
            }
        }
        cout << i << (prime == true ? " prime number" : " not prime number") << endl;
    }
}
