#include <iostream>

using namespace std;

bool doSomething(bool b1, bool b2);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true, true) == false ? "passed" : "failed") << endl;
    cout << (doSomething(false, true) == true ? "passed" : "failed") << endl;
    cout << (doSomething(true, false) == true ? "passed" : "failed") << endl;
    cout << (doSomething(false, false) == false ? "passed" : "failed") << endl;


    return 0;
}

bool doSomething(bool b1, bool b2)
{
    bool result{false};

    if (!(b1 && b2))
    {
        if (b1 || b2)
        {
            result = true;
        }
    }
    return result;
}
