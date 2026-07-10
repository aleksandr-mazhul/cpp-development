#include <iostream>
using namespace std;

int main()
{
    srand(time(0));
    int limit = rand() % 1'000;
    cout << limit << endl;

    int sum{}, count{};
    // while (true)
    // {
    //     int value = rand() % 100 - rand() % 100;
    //     sum += value;
    //     count++;
    //     if (sum >= limit) {
    //         break;
    //     }
    // }

    // for (; true; count++) {
    //     int value = rand() % 100 - rand() % 100;
    //     sum += value;
    //     if (sum >= limit) {
    //         break;
    //     }
    // }

    int value{};
    cout << " Please enter a 2-digit number: ";
    while (cin >> value)
    {
        if (abs(value) > 100 || abs(value) < 10)
        {
            cout << "❌ Please enter a 2-digit number: ";
            continue;
        }
        sum += value;
        count++;
        if (sum >= limit)
        {
            break;
        }
    }


    cout << "" << sum << endl;
    cout << "number of counts" << count << endl;
    return 0;
}
