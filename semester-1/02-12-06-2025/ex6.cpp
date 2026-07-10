#include <iostream>

using namespace std;

int doSomething(int i);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(-4) == -4 ? "passed" : "failed") << endl;
    cout << (doSomething(-3) == -9 ? "passed" : "failed") << endl;
    cout << (doSomething(0) == 0 ? "passed" : "failed") << endl;
    cout << (doSomething(3) == -6 ? "passed" : "failed") << endl;
    cout << (doSomething(4) == 4 ? "passed" : "failed") << endl;

    return 0;
}

int doSomething(int i)
{
    int result{i};

    if (i < 0 && i >= -3)
    {
        result = i + 2 * i;
    }
    else if (i > 0 && i <= 3)
    {
        result = i - i * i;
    }

    return result;
}
