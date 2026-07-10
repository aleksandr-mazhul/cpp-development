#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int choice{}, a{}, b{};
    bool exit{true};
    do
    {
        cout << "1.Addition" << endl;
        cout << "2.Subtraction" << endl;
        cout << "3.Multiplication" << endl;
        cout << "4.Division" << endl;
        cout << "5.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter the numbers you want to add one by one" << endl;
            cin >> a;
            cin >> b;
            cout << "The sum is " << a + b << endl;
            continue;
        }
        else if (choice == 2)
        {
            cout << "Enter the number to subtract" << endl;
            cin >> a;
            cin >> b;
            cout << "The difference is " << a - b << endl;
            continue;
        }
        else if (choice == 3)
        {
            cout << "Enter the numbers to be converted" << endl;
            cin >> a;
            cin >> b;
            cout << "Multiplication " << a * b << endl;
            continue;
        }
        else if (choice == 4)
        {
            cout << "Enter the numbers to be divided" << endl;
            cin >> a;
            cin >> b;
            cout << "Division " << a / b << endl;
            continue;
        }
        else if (choice == 5)
        {
            exit = false;
        }
        else
        {
            cout << "Invalid Choice.enter a number from 1 to 5" << endl;
        }
    }
    while (exit);
}
