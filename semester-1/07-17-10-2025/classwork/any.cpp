#include <iostream>
#include <string>
#include <climits>
using namespace std;

void getTypeOfSequence(long long, bool&, bool&, bool&);

string getTypeOfSequence(bool, bool, bool);

string getTypeOfSequence(long long);


void menu();

int main()
{
    menu();
}

void getTypeOfSequence(long long number, bool& lessThan, bool& equal, bool& moreThan)
{
    lessThan = moreThan = equal = false;
    number = abs(number);
    int next = static_cast<int>(number % 10);
    number /= 10;
    while (number)
    {
        int previous = static_cast<int>(number % 10);
        if (next > previous)
        {
            lessThan = true;
        }
        else if (next < previous)
        {
            moreThan = true;
        }
        else
        {
            equal = true;
        }
        next = previous;
        number /= 10;
    }
}

string getTypeOfSequence(bool lessThan, bool moreThan, bool equal)
{
    if (!lessThan && equal && !moreThan)
    {
        return "monotonic sequence";
    }
    if (lessThan && equal && !moreThan)
    {
        return "not strictly descending sequence";
    }
    if (lessThan && !equal && !moreThan)
    {
        return "strictly descending sequence";
    }
    if (!lessThan && equal && moreThan)
    {
        return "not strictly increasing sequence";
    }
    if (!lessThan && !equal && moreThan)
    {
        return "strictly increasing sequence";
    }
    return "chaotic sequence";
}

string getTypeOfSequence(long long number)
{
    bool lessThan{}, equal{}, moreThan{};
    getTypeOfSequence(number, lessThan, equal, moreThan);
    return getTypeOfSequence(lessThan, moreThan, equal);
}


void menu()
{
    int chose{0};
    cout << "enter a number to select the appropriate mode." << endl;
    cout << "enter 1 for manual verification, enter 2 for script verification " << endl;

    while (cin >> chose)
    {
        if (chose == 1)
        {
            long long number{0};
            cout << "enter a number to check its properties." << endl;
            cout << "enter a number 0 to exit." << endl;
            while (cin >> number)
            {
                if (number == 0)
                {
                    cout << "enter a number to select  mode." << endl;
                    cout << "enter 1 for manual , enter 2 for script  " << endl;
                    break;
                }
                cout << getTypeOfSequence(number) << endl;
                cout << "next number:" << endl;
            }
        }
        else if (chose == 2)
        {
            cout << "11111111111 " << getTypeOfSequence(11111111111) << endl;
            cout << "358373 " << getTypeOfSequence(358373) << endl;
            cout << "35689 " << getTypeOfSequence(35689) << endl;
            cout << "98765 " << getTypeOfSequence(98765) << endl;
            cout << "11256 " << getTypeOfSequence(11256) << endl;
            cout << "997644 " << getTypeOfSequence(997644) << endl;
            cout << "-11111111111 " << getTypeOfSequence(11111111111) << endl;
            cout << "-358373 " << getTypeOfSequence(358373) << endl;
            cout << "-35689 " << getTypeOfSequence(35689) << endl;
            cout << "-98765 " << getTypeOfSequence(98765) << endl;
            cout << "-11256 " << getTypeOfSequence(11256) << endl;
            cout << "-997644 " << getTypeOfSequence(997644) << endl;
            cout << "LLONG_MIN " << getTypeOfSequence(LLONG_MIN) << endl;
        }
        else
        {
            cout << "enter 1 for manual, enter 2 for script " << endl;
        }
    }
}
