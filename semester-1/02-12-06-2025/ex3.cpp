#include <iostream>

using namespace std;

bool doSomething(bool b1);

int main()
{
    cout << "doSomething" << endl;
    cout << (doSomething(true) == false ? "passed" : "failed") << endl;
    cout << (doSomething(false) == true ? "passed" : "failed") << endl;


    return 0;
}

bool doSomething(bool b)
{
    bool result{true};

    if (b)
    {
        result = false;
    }
    return result;
}
