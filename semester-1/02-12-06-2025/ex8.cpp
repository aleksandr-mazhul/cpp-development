#include <iostream>

using namespace std;

int doSomething(bool b, int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true, -7) ? "passed" : "failed") << endl;
    cout << (!doSomething(true, -5) ? "passed" : "failed") << endl;
    cout << (doSomething(true, -1) ? "passed" : "failed") << endl;
    cout << (!doSomething(true, -0) ? "passed" : "failed") << endl;
    cout << (doSomething(true, 2) ? "passed" : "failed") << endl;
    cout << (!doSomething(true, 5) ? "passed" : "failed") << endl;
    cout << (doSomething(true, 10) ? "passed" : "failed") << endl;


    cout << (doSomething(false, -19) ? "passed" : "failed") << endl;
    cout << (!doSomething(false, -5) ? "passed" : "failed") << endl;
    cout << (doSomething(false, -2) ? "passed" : "failed") << endl;
    cout << (!doSomething(false, 0) ? "passed" : "failed") << endl;
    cout << (doSomething(false, 2) ? "passed" : "failed") << endl;
    cout << (!doSomething(false, 5) ? "passed" : "failed") << endl;
    cout << (doSomething(false, 7) ? "passed" : "failed") << endl;

    return 0;
}

int doSomething(bool b, int i)
{
    bool result{};

    if (b)
    {
        if ((i >= -3 && i < 0) || i < -6)
        {
            result = true;
        }
        else if ((i <= 3 && i > 0) || i > 6)
        {
            result = true;
        }
    }

    else if (!b)
    {
        result = true;
        if (i == 0)
        {
            result = false;
        }
        else if ((i <= -3 && i >= -6) || (i >= 3 && i <= 6))
        {
            result = false;
        }
    }

    return result;
}
