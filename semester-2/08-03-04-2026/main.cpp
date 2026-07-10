#include "sorting_utils.h"

#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    constexpr int data[] = {-34, 70, 12, -3, 50, 51, -100, 42, 98};
    constexpr int n = sizeof data / sizeof data[0];

    int array[n];

    auto copyFromData = [&]()
    {
        for (int i = 0; i < n; i++)
            array[i] = data[i];
    };
    Array<int> arr{};
    Array<std::string> convertedArr =
        convert<int, std::string>(arr, [](const std::string&, int x) { return std::to_string(x); });

    for (int i = 0; i < n; i++)
    {
        std::cout << convertedArr[i] << " ";
    }
    std::cout << std::endl;


    Array<std::string> convertedArr1 = convert<int, std::string>(
        arr, [](const std::string&, int x) { return std::to_string(x * 2) + ' '; });

    for (int i = 0; i < n; i++)
    {
        std::cout << convertedArr1[i] << " ";
    }
    std::cout << std::endl;


    Array<bool> checker = convert<int, bool>(arr, [](bool, int x) { return x > 0; });
    for (int i = 0; i < n; i++)
    {
        std::cout << checker[i] << " ";
    }
    std::cout << std::endl;


    copyFromData();
    bubbleSort < int, int, int(*)
    (int)
    >
    (array, 0, n - 1, keyAbs);
    display < int, 0, n - 1 > (array);

    copyFromData();
    int l{4};
    bubbleSort<int, int, std::function<int(int)>>(
        array, 0, n - 1, [l](int x) { return ((x % l) + l) % l; });
    display < int, 0, n - 1 > (array);

    copyFromData();
    std::cout << "Using comparer:" << std::endl;
    bubbleSort<int>(array, 0, n - 1, [](int x, int y) { return std::abs(x) < std::abs(y); });
    display < int, 0, n - 1 > (array);

    copyFromData();
    std::cout << "Using comparer:" << std::endl;
    bubbleSort<int>(array, 0, n - 1, [](int x, int y) { return std::abs(x) > std::abs(y); });
    display < int, 0, n - 1 > (array);

    copyFromData();
    std::cout << "Using comparer:" << std::endl;
    bubbleSort<int>(
        array, 0, n - 1, [](int x, int y) { return std::to_string(x)[1] < std::to_string(y)[1]; });
    display < int, 0, n - 1 > (array);

    copyFromData();
    std::cout << "Using std::sort:" << std::endl;
    std::sort(
        array, array + n, [](int x, int y) { return std::to_string(x)[1] > std::to_string(y)[1]; });
    display < int, 0, n - 1 > (array);
    //-----------------------------

    constexpr double data1[] = {-34.5, 7.34, 12.2, -3.12, 0, 5, -100, 42, 9.1234};
    constexpr int n1 = sizeof data1 / sizeof data1[0];

    double array1[n1];

    auto copyFromData1 = [&]()
    {
        for (int i = 0; i < n1; i++)
            array1[i] = data1[i];
    };

    copyFromData1();
    bubbleSort<double, char, std::function<char(double)>>(
        array1, 0, n1 - 1, [](double x) { return std::to_string(x)[0]; });
    display < double, 0, n1 - 1 > (array1);

    copyFromData1();
    bubbleSort<double, std::string, std::function<std::string(double)>>(
        array1, 0, n1 - 1, [](double x) { return std::to_string(x) + "$"; });
    display < double, 0, n1 - 1 > (array1);

    copyFromData1();
    std::cout << "Using std::sort:" << std::endl;
    std::sort(array1, array1 + n1);
    display < double, 0, n1 - 1 > (array1);
    return 0;
}
