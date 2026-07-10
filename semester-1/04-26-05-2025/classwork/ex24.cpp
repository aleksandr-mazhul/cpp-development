#include <iostream>
using namespace std;

int main()
{
    int number{1};
    do
    {
        cout << number << (number == 5 ? ". " : ", ");
        number++;
    }
    while (number <= 5);
}
