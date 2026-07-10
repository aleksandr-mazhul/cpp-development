#include <iostream>

using namespace std;

int doSomething(int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(-6) == -6 ? "passed" : "failed") << endl;
    cout << (doSomething(-5) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(0) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(4) == -1 ? "passed" : "failed") << endl;
    cout << (doSomething(5) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(6) == 6 ? "passed" : "failed") << endl;

    return 0;
}

int doSomething(int i)
{
    int result{i};

    if (result < 0)
    {
        if (i >= -5)
        {
            result = i + 5;
        }
    }
    else if (i > 0)
    {
        if (i <= 5)
        {
            result = i - 5;
        }
    }

    return result;
}
