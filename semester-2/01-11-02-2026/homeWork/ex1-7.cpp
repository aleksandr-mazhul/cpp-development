#include <iostream>
using namespace std;


// 1
int setBit(int number, int bitPosition)
{
    return number | (1 << bitPosition);
}


// 2
bool isBitSet(int number, int bitPosition)
{
    return (number & (1 << bitPosition)) != 0;
}


// 3
int invertBits(int number)
{
    int size = sizeof(number) * 8;
    int result = number;
    for (size_t i = 0; i < size; ++i)
    {
        result ^= (1 << i);
    }
    return result;
}


// 4
int countOfBits(int number)
{
    int size = sizeof(number) * 8;
    int count = 0;
    for (size_t i = 0; i < size; ++i)
    {
        if (number & (1 << i))
        {
            count++;
        }
    }
    return count;
}


// 5
int setBitsOnMask(int number, int mask)
{
    return number | mask;
}


// 6
enum Flags
{
    None = 0,
    Sound = 1 << 0,
    Music = 1 << 1,
    Light = 1 << 2,
    Vibration = 1 << 3
};

void printEnabledFlags(int settings)
{
    if (settings & Sound)
        cout << "Sound включен\n";

    if (settings & Music)
        cout << "Music включен\n";

    if (settings & Light)
        cout << "Light включен\n";

    if (settings & Vibration)
        cout << "Vibration включен\n";

    if (settings == None)
        cout << "Ничего не включено\n";
}


// 7
void swap(int& a, int& b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}


int main()
{
    // 1
    int x = setBit(0, 9);
    cout << x << endl;

    // 2
    cout << boolalpha << isBitSet(827349728942, 1) << endl;

    // 3
    cout << invertBits(128) << endl;

    // 4
    cout << countOfBits(5) << endl;

    // 5
    cout << setBitsOnMask(5, 28) << endl;

    // 6

    int settings = Music | Light;
    printEnabledFlags(settings);


    // 7
    int a = 5;
    int b = 3;

    swap(a, b);

    std::cout << "x = " << a << "\n";
    std::cout << "y = " << b << "\n";

    return 0;
}



