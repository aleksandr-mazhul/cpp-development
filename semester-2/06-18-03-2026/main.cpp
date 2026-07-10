#include <array>
#include <functional> //function<>
#include <iostream>

using namespace std;

constexpr size_t Size = 10;

using PredicatePointer = bool (*)(int);
using IntegerArray = array<int, Size>;
using Predicate = function<bool(int)>; // function pointer, functors & lambds

void filterOnlyPositive(const IntegerArray& numbers);
void filterOnlyNegative(const IntegerArray& numbers);
void filterOnlyEven(const IntegerArray& numbers);
void filterOnlyOdd(const IntegerArray& numbers);
void filterByPredicate(const IntegerArray& numbers, PredicatePointer predicate);
void filterByPredicate(const IntegerArray& numbers, Predicate predicate);
bool isPositive(int x);
bool isNegative(int x);
bool isEven(int x);
bool isOdd(int x);

bool isEquals(int x, int value)
{
    return x == value;
}

bool isRangeIn(int x, int up, int down)
{
    return x <= up && x >= down;
}

//.......

struct PositivePredicate
{
    inline bool operator()(int x) const
    {
        return x > 0;
    }
};

struct NegativePredicate
{
    inline bool operator()(int x) const
    {
        return x < 0;
    }
};

struct OddPredicate
{
    inline bool operator()(int x) const
    {
        return x % 2;
    }
};

struct EvenPredicate
{
    inline bool operator()(int x) const
    {
        return !(x % 2);
    }
};

class EqualsPredicate
{
public:
    EqualsPredicate(int value)
        : value{value}
    {
        // this->value = value;
    }

    inline bool operator()(int x) const
    {
        return x == value;
    }

private:
    int value;
};

class RangePredicate
{
public:
    RangePredicate(int down, int up)
        : down{down}
          , up{up}
    {
        // this->value = value;
    }

    inline bool operator()(int x) const
    {
        return x <= up && x >= down;
    }

private:
    int down, up;
};

int main()
{
    IntegerArray numbers{2, 3, 4, -5, 60, 12, -87, 2, 2, 3};
    int value = 2;
    /*filterOnlyPositive(numbers);
    cout << endl;
    filterOnlyNegative(numbers);
    cout << endl;
    filterOnlyEven(numbers);
    cout << endl;
    filterOnlyOdd(numbers);
    cout << endl;*/
    // PositivePredicate p1{};
    /*std::array<PredicatePointer, 4> predicates{ isPositive, isNegative, isEven, isOdd};
    for (size_t i = 0; i < predicates.size(); i++)
    {
      filterByPredicate(numbers, predicates[i]);
      cout << endl;
    }*/
    /*Predicate p{ isPositive };
    p = p1;
    cout << p(56) << endl;
    p = NegativePredicate();*/
    std::array<Predicate, 13> functors{
        NegativePredicate(),
        PositivePredicate(),
        OddPredicate(),
        EvenPredicate(),
        isPositive,
        isNegative,
        isEven,
        isOdd,
        EqualsPredicate(2),
        EqualsPredicate(3),
        RangePredicate(1, 12),
        [](int x) { return x > 0; },
        [value](int x) { return x == value; },
    };
    for (size_t i = 0; i < functors.size(); i++)
    {
        filterByPredicate(numbers, functors[i]);
        cout << endl;
    }
}

void filterOnlyPositive(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] > 0)
        {
            cout << numbers[i] << " ";
        }
    }
}

void filterOnlyNegative(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < 0)
        {
            cout << numbers[i] << " ";
        }
    }
}

void filterOnlyEven(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (!(numbers[i] % 2))
        {
            cout << numbers[i] << " ";
        }
    }
}

void filterOnlyOdd(const IntegerArray& numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] % 2)
        {
            cout << numbers[i] << " ";
        }
    }
}


void filterByPredicate(const IntegerArray& numbers, PredicatePointer predicate)
{
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (predicate(numbers[i]))
        {
            cout << numbers[i] << " ";
        }
    }
}

void filterByPredicate(const IntegerArray& numbers, Predicate predicate)
{
    for (auto number : numbers)
    {
        if (predicate(number))
        {
            cout << number << " ";
        }
    }
}


bool isPositive(int x)
{
    return x > 0;
}

bool isNegative(int x)
{
    return x < 0;
}

bool isEven(int x)
{
    return !(x % 2);
}

bool isOdd(int x)
{
    return x % 2;
}
