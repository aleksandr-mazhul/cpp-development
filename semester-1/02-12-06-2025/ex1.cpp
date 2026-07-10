#include <iostream>

using namespace std;

int doSomething(int i); //prototype

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(-123) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(-13) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(-123000) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(0) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(123) == 123 ? "passed" : "failed") << endl;
    cout << (doSomething(145) == 145 ? "passed" : "failed") << endl;
    cout << (doSomething(1) == 1 ? "passed" : "failed") << endl;
    return 0;
}

int doSomething(int i)
{
    int result{i};

    if (result < 0)
    {
        result = 0;
    }

    return result;
}
