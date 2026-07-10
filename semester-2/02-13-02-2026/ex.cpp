#include <iostream>
using namespace std;


enum TypeOfSequence
{
    Equals = 0,
    Less = 1 << 0,
    More = 1 << 1,
};


int main()
{
    int seq = Equals | Less;
    int state = 0;

    for (std::size_t i = 0; i < length; ++i)
    {
        if (array[i] < array[i + 1])
        {
            state |= static_cast<itn>(TypeOfSequence::Less);
        }
        else if (array[i] > array[i + 1])
        {
            state |= static_cast<itn>(TypeOfSequence::More);
        }
        else
        {
            state |= static_cast<itn>(TypeOfSequence::Equals);
        }
    }

    switch (state)
    {
    case Equals: return "monotonus";
    case Less: return "strictly decreasing";
    case More: return "strictly increasing";
    case Less | More: return "strictly increasing";
    case Equals | More: return "increasing";
    default: return "mixed";
    }
}
