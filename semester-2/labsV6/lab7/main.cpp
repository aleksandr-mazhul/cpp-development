#include "algorithms.h"
#include "tests.h"
#include <array>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cin >> std::boolalpha;
    array < int, 10 > arr;

    initArray(arr, -100, 200);

    cout << "Исходный массив:\n";
    printArray(arr);

    transformArray(arr,
                   [](int x)
                   {
                       if (abs(x) < 10)
                           return abs(x);
                       return x;
                   });

    cout << "\nПосле части 1:\n";
    printArray(arr);

    int count = countIf(arr, [](int el) { return el < -10; });
    cout << "\nПосле части 2:\n";
    cout << "Количество элементов < -10: " << count << endl;

    int first = findIf(arr, [](int x) { return x > 5; });
    cout << "Первый элемент > 5: " << first << endl;

    sortArray(arr, [](int a, int b) { return abs(a) < abs(b); });

    cout << "\nПосле части 3:\n";
    printArray(arr);

    runTests();
    return 0;
}
