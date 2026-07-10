#include <iostream>;
using namespace std;

int main()
{
    double le;
    cout << "Enter the number of light years:" << endl;
    cin >> le;
    double au = le * 63240;
    cout << le << "light years =" << au << "astronomical units" << endl;
}
