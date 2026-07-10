#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int random_in_range = rand() % 100 + 1;
    cout << "A number from 1 to 100 is guessed. Try to guess it!" << endl;

    int i{1};
    bool guessed{true};
    while (guessed == true)
    {
        int guess{};
        cout << "Your guess:" << endl;
        cin >> guess;

        if (guess == random_in_range)
        {
            cout << "Congratulations! You guessed it in " << i << " attempts!" << endl;
            break;
        }
        else if (guess > random_in_range)
        {
            cout << "The guessed number is smaller!" << endl;
        }
        else if (guess < random_in_range)
        {
            cout << "The guessed number is greater!" << endl;
        }
        i++;
    }
}
