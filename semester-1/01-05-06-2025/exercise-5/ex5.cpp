#include <iostream>
using namespace std;

int main()
{
    int Celsius;
    cout << "Please enter a Celsius value:" << endl;
    cin >> Celsius;
    cout << Celsius << "degrees Celsius is" << 1.8 * Celsius + 32 << "degrees Fahrenheit." << endl;
    return 0;
}
