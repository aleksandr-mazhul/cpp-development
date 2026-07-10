#include "Array.h"

Array::Array()
{
    source = new int[capacity];
}

void Array::add(int element)
{
    if (length == capacity)
    {
        capacity *= growFactor;
        int* temp = new int[capacity];

        for (size_t i{0}; i < length; i++)
        {
            temp[i] = source[i];
        }
        delete[] source;
        source = temp;
    }


    source[length++] = element;
}

int* Array::getSource() const
{
    return source;
}

int Array::getLength() const
{
    return length;
}

std::ostream& operator<<(std::ostream& os, const Array& aray)
{
    os << " Elements of array ";
    os << "[";
    for (size_t i{0}; i < aray.getLength(); i++)
    {
        os << aray.getSource()[i] << " ";
    }
    os << "]";

    return os;
}
