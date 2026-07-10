#include <iostream>

using namespace std;

int doSomething(bool b1, bool b2, int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true, true, -10) == -10 ? "passed1" : "failed1") << endl;
    cout << (doSomething(true, true, -9) == -4 ? "passed2" : "failed2") << endl;
    cout << (doSomething(true, true, -5) == 0 ? "passed3" : "failed3") << endl;
    cout << (doSomething(true, true, -2) == 3 ? "passed4" : "failed4") << endl;
    cout << (doSomething(true, true, 0) == -1 ? "passed5" : "failed5") << endl;
    cout << (doSomething(false, true, -15) == -14 ? "passed6" : "failed6") << endl;
    cout << (doSomething(false, true, -10) == -9 ? "passed7" : "failed7") << endl;
    cout << (doSomething(false, false, 5) == 5 ? "passed8" : "failed8") << endl;
    cout << (doSomething(false, false, 100) == 100 ? "passed9" : "failed9") << endl;


    return 0;
}

int doSomething(bool b1, bool b2, int i)
{
    int result{i};

    if (b1)
    {
        if (i == 0)
        {
            result = -1;
        }
        else if (i >= 2 && i <= 9)
        {
            if (b2)
            {
                result = 10 - result;
            }
            else
            {
                result = 10 + result;
            }
        }
        else if (i <= -2 && i >= -9)
        {
            if (b2)
            {
                result = 5 + result;
            }
            else
            {
                result = 5 - result;
            }
        }
    }
    else
    {
        if (i == 0)
        {
            if (b2)
            {
                result = 1;
            }
            else
            {
                result = -1;
            }
        }
        else if (b2)
        {
            if (i <= -10 || i >= 10)
            {
                result = result + 1;
            }
        }
        else
        {
            if (i <= -10 || i >= 10)
            {
                result = result - 1;
            }
        }

        if (i != 0 && i > -5 && i < 5)
        {
            if (b2)
            {
                result = result + 10;
            }
            else
            {
                result = result - 10;
            }
        }
    }
    return result;
}

// почему в последнем false?
// если в посденем брать от 5 до 9, то оно раьотает, я если больше -- то нет.
