#include <iostream>
using namespace std;

void getTypeOfSequence(long long, bool&, bool&, bool&);

int main()
{
    bool lessThen{0}, moreThan{0}, equal{0};
    getTypeOfSequence(987654321, lessThen, moreThan, equal);
    cout << equal << lessThen << moreThan << endl;
    getTypeOfSequence(-987654321, lessThen, moreThan, equal);
    cout << equal << lessThen << moreThan << endl;
    getTypeOfSequence(998776544321, lessThen, moreThan, equal);
    cout << equal << lessThen << moreThan << endl;
    getTypeOfSequence(-998776544321, lessThen, moreThan, equal);
    cout << equal << lessThen << moreThan << endl;
    getTypeOfSequence(123456789, lessThen, moreThan, equal);
    getTypeOfSequence(-123456789, lessThen, moreThan, equal);
    getTypeOfSequence(112344566789, lessThen, moreThan, equal);
    getTypeOfSequence(-112344566789, lessThen, moreThan, equal);
    getTypeOfSequence(1111111111, lessThen, moreThan, equal);
    getTypeOfSequence(-1111111111, lessThen, moreThan, equal);
    getTypeOfSequence(1762157651761481, lessThen, moreThan, equal);
    getTypeOfSequence(-1762157651761481, lessThen, moreThan, equal);
}

void getTypeOfSequence(long long number, bool& lessThen, bool& moreThan, bool& equal)
{
    lessThen = false;
    moreThan = false;
    equal = false;
    if (number < 0) number = -number;

    int next = static_cast<int>(number % 10);
    number /= 10;

    while (number)
    {
        int previous = static_cast<int>(number % 10);
        if (next > previous)
        {
            lessThen = true;
        }
        else if (next < previous)
        {
            moreThan = true;
        }
        else
        {
            equal = true;
        }
        next = previous;
        number /= 10;
    }
}
