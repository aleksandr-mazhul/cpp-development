#include <iostream>
using namespace std;


int main()
{
    system("cls");
    cout << "Enter a latitude in degrees, minutes, and seconds:" << endl;

    double degrees;
    cout << "First, enter the degrees:" << endl;
    cin >> degrees;

    double minutes;
    cout << "Next, enter the minutes of arc:" << endl;
    cin >> minutes;

    double seconds;
    cout << "Finally, enter the seconds of arc:" << endl;
    cin >> seconds;

    double result = degrees + minutes / 60 + seconds / 3600;

    cout << degrees << "degrees," << minutes << "minutes," << seconds << "seconds=" << result << endl;
    return 0;
}
