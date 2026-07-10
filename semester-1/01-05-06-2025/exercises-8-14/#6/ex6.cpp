#include <iostream>
using namespace std;
const int km = 100;

int main()
{
    system("cls");
    double distance;
    cout << "Enter the distance in kilometers:" << endl;
    cin >> distance;

    double gasoline;
    cout << "Enter the amount of spent gasoline:" << endl;
    cin >> gasoline;

    double consumption = (km * gasoline) / distance;


    cout << "Fuel consumption:" << consumption << "/" << km << "km" << endl;
    return 0;
}
