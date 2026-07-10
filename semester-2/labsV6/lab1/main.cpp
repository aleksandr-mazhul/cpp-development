#include <iostream>
#include "array_utils.cpp"
#include "tests.cpp"
using namespace std;

int main()
{
    // ---------------------------
    // ДЕМО (обязательное)
    // ---------------------------
    int n;
    double minValue, maxValue;

    cin >> n;
    cin >> minValue >> maxValue;

    double* a = new double[n];
    initArray(a, n, minValue, maxValue);

    cout << "Исходный массив:\n";
    printArray(a, n);

    cout << "\nПосле Часть 1 (reverse):\n";
    reverse(a, n, 0, n - 1);
    printArray(a, n);

    cout << "\nПосле Часть 2 (cyclicLeftShift):\n";
    cyclicLeftShift(a, n, n - 1, 0, n - 1);
    printArray(a, n);

    cout << "\nПосле Часть 3 (selectionSort):\n";
    selectionSort(a, n, 0, n - 1);
    printArray(a, n);

    delete[] a;

    // ---------------------------
    // ТЕСТЫ (обязательное)
    // ------------------ ---------
    printTestResult("initArray range", testInitArrayRange());
    printTestResult("reverse full array", testReverseFullArray());
    printTestResult("cyclic left shift", testCyclicLeftShift());
    printTestResult("selection sort", testSelectionSort());

    return 0;
}

