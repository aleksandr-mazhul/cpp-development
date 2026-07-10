#include <iostream>
using namespace std;

int main()
{
    int number;

    do
    {
        cout << "Enter your number: ";
        cin >> number;
        cout << (number < 1 || number > 10 ? "Invalid input. Try again." : "") << endl;
    }
    while (number < 1 || number > 10);

    cout << "Thank you! You entered: " << number;
    return 0;
}
