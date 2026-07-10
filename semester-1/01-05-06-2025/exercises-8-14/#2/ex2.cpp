#include <iostream>
#include <cmath>
using namespace std;
const int foot_inch = 12;
const double inch_meter = 0.0254;
const double pound_kg = 2.2;

int main()
{
    int foot;
    cout << "How many foot are in you:" << endl;
    cin >> foot;

    int inches;
    cout << "How many inches are in you:" << endl;
    cin >> inches;

    int pounds;
    cout << "Enter your weight in pounds:" << endl;
    cin >> pounds;

    double total_inch = foot * foot_inch + inches;
    double height_meter = total_inch * inch_meter;
    double weight_kg = pounds / pound_kg;

    double BMI = weight_kg / (pow(height_meter, 2));

    cout << "BMI =" << BMI << endl;
    return 0;
}
