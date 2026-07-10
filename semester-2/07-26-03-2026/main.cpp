#include <functional>
#include <iostream>

// using FunctionKey = std::function<int(int)>;

int keyAbs(int x);
int keyDigitCount(int x);
int keySumOfDigits(int x);
int keyLastDigit(int x);
int keyModulo(int x, int n);


template <typename T, size_t left, size_t right>
void display(const T* arr);
// void bubbleSort(int* const arr, int left, int right, bool order);

template <typename T, typename U, typename FunctionKey>
void bubbleSort(T* arr, int left, int right, FunctionKey key);

// todo
//  template<typename T, typename U>
//  void bubbleSort(T* const arr, int left, int right, U* key);

void bubbleSortByValueAsc(int* arr, int left, int right);
void bubbleSortByValueDesc(int* arr, int left, int right);
void bubbleSortByAbs(int* arr, int left, int right);
void bubbleSortByDigitCount(int* arr, int left, int right);
void bubbleSortBySumOfDigits(int* arr, int left, int right);
void bubbleSortByLastDigit(int* arr, int left, int right);

int main()
{
    constexpr int data[] = {-34, 7, 12, -3, 0, 5, -100, 42, 9};
    constexpr int n = sizeof data / sizeof data[0];

    int array[n];

    auto copyFromData = [&]()
    {
        for (int i = 0; i < n; i++)
            array[i] = data[i];
    };

    copyFromData();
    bubbleSort<int, int, int (*)(int)>(array, 0, n - 1, keyAbs);
    display<int, 0, n - 1>(array);

    copyFromData();
    int l{4};
    bubbleSort<int, int, std::function<int(int)>>(array, 0, n - 1, [l](int x) { return ((x % l) + l) % l; });
    display<int, 0, n - 1>(array);


    constexpr double data1[] = {-34.5, 7.34, 12.2, -3.12, 0, 5, -100, 42, 9.1234};
    constexpr int n1 = sizeof data1 / sizeof data1[0];

    double array1[n1];

    auto copyFromData1 = [&]()
    {
        for (int i = 0; i < n1; i++)
            array1[i] = data1[i];
    };

    copyFromData1();
    bubbleSort<double, char, std::function<char(double)>>(array1, 0, n1 - 1,
                                                          [](double x) { return std::to_string(x)[0]; });
    display<double, 0, n1 - 1>(array1);
    return 0;
}

template <typename T, size_t left, size_t right>
void display(const T* arr)
{
    for (int i = left; i <= right; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

// --- Вспомогательные функции для ключей сортировки ---

int keyAbs(int x) { return std::abs(x); }

int keyDigitCount(int x)
{
    if (x == 0)
        return 1;
    int n = 0;
    int t = std::abs(x);
    while (t)
    {
        t /= 10;
        ++n;
    }
    return n;
}

int keySumOfDigits(int x)
{
    int t = std::abs(x);
    int s = 0;
    while (t)
    {
        s += t % 10;
        t /= 10;
    }
    return s;
}

int keyLastDigit(int x) { return std::abs(x % 10); }

// Остаток от деления на N (нормализованный для отрицательных)
int keyModulo(int x, int n) { return ((x % n) + n) % n; }

// 1. Обычная сортировка по значению (сравнение «меньше» / «больше»)
void bubbleSort(int* const arr, int left, int right, bool order)
{
    for (int i{left}; i < right; i++)
    {
        for (int j{right}; j > i; j--)
        {
            if (order)
            {
                if (arr[j] < arr[j - 1])
                    std::swap(arr[j], arr[j - 1]);
            }
            else
            {
                if (arr[j] > arr[j - 1])
                    std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

// --- Много вариантов самой сортировки (критерий «зашит» в коде) — затем сворачиваются в одну с
// настройкой ---

void bubbleSortByValueAsc(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (arr[j] < arr[j - 1])
                std::swap(arr[j], arr[j - 1]);
}

template <typename T, typename U, typename FunctionKey>
void bubbleSort(T* const arr, int left, int right, FunctionKey key)
{
    int n = right - left + 1;
    U* keys = new U[n];

    for (int i{0}; i < n; i++)
    {
        keys[i] = key(arr[i + left]);
    }

    for (int i{0}; i < n; i++)
        for (int j{n - 1}; j > i; j--)
            if (keys[j] < keys[j - 1])
            {
                std::swap(keys[j], keys[j - 1]);
                std::swap(arr[j + left], arr[j - 1 + left]);
            }
    delete[] keys;
}

void bubbleSortByValueDesc(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (arr[j] > arr[j - 1])
                std::swap(arr[j], arr[j - 1]);
}

void bubbleSortByAbs(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (std::abs(arr[j]) < std::abs(arr[j - 1]))
                std::swap(arr[j], arr[j - 1]);
}

void bubbleSortByDigitCount(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (keyDigitCount(arr[j]) < keyDigitCount(arr[j - 1]))
                std::swap(arr[j], arr[j - 1]);
}

void bubbleSortBySumOfDigits(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (keySumOfDigits(arr[j]) < keySumOfDigits(arr[j - 1]))
                std::swap(arr[j], arr[j - 1]);
}

void bubbleSortByLastDigit(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
        for (int j{right}; j > i; j--)
            if (keyLastDigit(arr[j]) < keyLastDigit(arr[j - 1]))
                std::swap(arr[j], arr[j - 1]);
}
