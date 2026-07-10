#include <iostream>
using namespace std;

inline TypeOfsequence operator|(const TypeOfsequence lhs, const TypeOfsequence rhs);

enum class TypeOfSequence
{
    Equals = 1, // 1 << 0
    Less = 2, // 1 << 1
    More = 4, // 1 << 2
};

void displayArray(int* array, size_t n);

string getTypeOfSequence(const int* array, size_t n);

int main()
{
    const size_t n = 5;
    int array[n] = {1, 2, 3, 4, 5};
    cout << "Sequence ";
    displayArray(array, n);
    cout << getTypeOfSequence(array, n) << endl;
}

void displayArray(int* array, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
}

string getTypeOfSequence(const int* array, size_t n)
{
    // bool less{false}, more{false}, equals{false};
    TypeOfSequence state{};

    for (size_t i = 0; i < n - 1; i++)
    {
        if (array[i] < array[i + 1])
        {
            state |= TypeOfSequence::Less
        }
        else if (array[i] > array[i + 1])
        {
            state |= TypeOfSequence::More;
        }
        else
        {
            state |= TypeOfSequence::Equals;
        }
    }

    switch (state)
    {
    case Equals: return "Monotonus";
    case Less: return "Stricly increasing";
    case More: return "Stricly decreasing";
    case More | Equals: return "Decreasing";
    case Less | Equals: return "Increasing";
    default: return "Chaotic";
    }
}

inline TypeOfsequence operator|(const TypeOfsequence lhs, const TypeOfsequence rhs)
{
    return static_cast<lhs> lh;
}


s

