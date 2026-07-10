#include <iostream>

using namespace std;

int doSomething(bool b, int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true, -10) == -10 ? "passed" : "failed") << endl;
    cout << (doSomething(true, -7) == -7 ? "passed" : "failed") << endl;
    cout << (doSomething(true, -5) == 12 ? "passed" : "failed") << endl;
    cout << (doSomething(true, 7) == 7 ? "passed" : "failed") << endl;
    cout << (doSomething(true, 15) == 15 ? "passed" : "failed") << endl;
    cout << (doSomething(false, -5) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(false, -10) == -5 ? "passed" : "failed") << endl;
    cout << (doSomething(false, 0) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(false, 5) == 10 ? "passed" : "failed") << endl;
    cout << (doSomething(false, 10) == 15 ? "passed" : "failed") << endl;


    return 0;
}

int doSomething(bool b, int i)
{
    int result{i};

    if (b)
    {
        if (i > -7 && i < 7)
        {
            result = 7 - i;
        }
    }
    else if (!b)
    {
        if (i <= -5 || i >= 5)
        {
            result = i + 5;
        }
    }


    return result;
}
