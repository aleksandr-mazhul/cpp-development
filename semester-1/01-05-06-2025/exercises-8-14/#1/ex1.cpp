#include <iostream>
using namespace std;
const int foot_inches = 12;
const double inches_cm = 2.54;

int main()
{
    system("cls");
    double cm;
    cout << "Enter the height in centimeters: _\b";
    cin >> cm;

    int TotalInch = cm / inches_cm;
    //вычисляем общее кол-во дюймов
    int foot = TotalInch / foot_inches;
    // находим сколько полынй футов находится в общем количесвк дюймов
    int Inch = TotalInch % foot_inches;
    //находим количество дюймов которые не вместились в целое кол-во футов как остаток от деления
    cout << "Height in inches:" << TotalInch << endl;
    cout << "Your height:" << foot << "foot" << Inch << "inch" << endl;
    return 0;
}
