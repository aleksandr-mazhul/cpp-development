#include <iostream>
using namespace std;
const double km_mile = 0.6214;
const double lit_gal = 0.264;


int main()
{
    system("cls");
    double lit_km;
    cout << "Enter the number of liters per 100 kilometers:" << endl;
    cin >> lit_km;

    double mile = 100 * km_mile;
    double gal = lit_km * lit_gal;

    double mile_gal = mile / gal;

    cout << "Answer" << mile_gal << "Miles per gallon" << endl;


    return 0;
}
