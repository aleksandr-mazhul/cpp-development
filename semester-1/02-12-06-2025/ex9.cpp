#include <iostream>

using namespace std;

int doSomething(bool b1, bool b2, int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true, true, -10) == -10 ? "passed" : "failed") << endl;
    cout << (doSomething(true, true, -9) == -4 ? "passed" : "failed") << endl;
    cout << (doSomething(true, true, -5) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(true, true, -2) == 3 ? "passed" : "failed") << endl;
    cout << (doSomething(true, true, 0) == -1 ? "passed" : "failed") << endl;
    cout << (doSomething(false, true, -15) == -14 ? "passed" : "failed") << endl;
    cout << (doSomething(false, true, -10) == -9 ? "passed" : "failed") << endl;
    cout << (doSomething(false, false, 5) == 5 ? "passed" : "failed") << endl;
    cout << (doSomething(false, false, 10) == 10 ? "passed" : "failed") << endl;


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

            else if (!b2)
            {
                result = 10 + result;
            }
        }
    }

    else if (i <= -2 && i >= -9)
    {
        if (b2)
        {
            result = 5 + result;
        }
        else if (!b2)
        {
            result = 5 - result;
        }
    }
    else if (!b1)
    {
        result = 1;
    }


    if (i == 0)
    {
        if (b2)
        {
            result = 1;
        }
        else if (!b2)
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
    else if (!b2)
    {
        if (i <= 10 || i >= 10)
        {
            result = result - 1;
        }
    }
    else if (i != 0 && i > -5 && i < 5)
    {
        if (b2)
        {
            result = result + 10;
        }
        else if (!b2)
        {
            result = result - 10;
        }
    }


    return result;
}
