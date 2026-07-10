#include <iostream>
using namespace std;

int main()
{
    system("cls");
    long long world;
    cout << "Enter the world's population:" << endl;
    cin >> world;

    long long amirica;
    cout << "Enter the population of the US:" << endl;
    cin >> amirica;

    double percente = (static_cast<double>(amirica) / world) * 100;
    cout << "The population of the US is" << percente << "%" << "of the world population." << endl;
    return 0;
}
