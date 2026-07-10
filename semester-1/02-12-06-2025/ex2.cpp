#include <iostream>

using namespace std;

int doSomething(int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(-6) == -36 ? "passed" : "failed") << endl;
    cout << (doSomething(-5) == 5 ? "passed" : "failed") << endl;
    cout << (doSomething(-2) == 2 ? "passed" : "failed") << endl;
    cout << (doSomething(0) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(10) == 10 ? "passed" : "failed") << endl;

    return 0;
}

int doSomething(int i)
{
    int result{i};

    if (result < 0 && result >= -5)
    {
        result = 0 - i;
    }
    else if (result < -5)
    {
        result = 0 - i * i;
    }
    return result;
}
