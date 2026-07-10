#pragma once
#include <iostream>

using namespace std;

class Array
{
public:
    Array();

    void add(int element);

    int* getSource() const;
    int getLength() const;

private:
    int* source;
    size_t capacity{4}; // текущая емкость массива, начинается с дефолтного значения 4
    size_t growFactor{2};
    size_t length{1};
};

std::ostream& operator<<(std::ostream& os, const Array& aray);
