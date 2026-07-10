#include <iostream>
using namespace std;

int main()
{
    const int SECONDS_PER_MINUTE = 60;
    const int MINUTES_PER_HOUR = 60;
    const int HOURS_PER_DAY = 24;


    long long total_seconds;


    cout << "Enter the number of seconds: ";
    cin >> total_seconds;


    int seconds = total_seconds % SECONDS_PER_MINUTE;
    int total_minutes = total_seconds / SECONDS_PER_MINUTE;
    int minutes = total_minutes % MINUTES_PER_HOUR;
    int total_hours = total_minutes / MINUTES_PER_HOUR;
    int hours = total_hours % HOURS_PER_DAY;
    int days = total_hours / HOURS_PER_DAY;


    cout << total_seconds << " seconds = "
        << days << " days, "
        << hours << " hours, "
        << minutes << " minutes, "
        << seconds << " seconds" << endl;

    return 0;
}
