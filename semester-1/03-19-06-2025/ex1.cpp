#include <iostream>
using namespace std;

int main()
{
    int i{1};
    while (i <= 10)
    {
        cout << i << (i == 10 ? ". " : ", ");
        // cout << i;
        // if (i == 10) {
        //     cout  << ".";
        // } 
        // else {
        //     cout  << ", ";
        // }
        i++;
    }
}
